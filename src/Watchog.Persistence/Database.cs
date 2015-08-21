using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AutoMapper;
using SQLite;
using Watchog.IPC;
using Watchog.Persistence.Models;

namespace Watchog.Persistence
{
    public class Database
    {
        private readonly SQLiteAsyncConnection _db;

        static Database()
        {
            Mapper.CreateMap<MovieWrapper, Movie>();
            Mapper.CreateMap<Movie, MovieWrapper>()
                .ConstructUsing((Func<ResolutionContext, MovieWrapper>) (r => new MovieWrapper()));
        }

        public Database(string path)
        {
            _db = new SQLiteAsyncConnection(path);
            _db.CreateTableAsync<Movie>().Wait();
        }

        public async Task ApplyChanges(List<Movie> movies)
        {
            var dbMovies = await _db.Table<Movie>().ToListAsync();

            var moviesToUpdate = new List<Movie>();
            var moviesToInsert = new List<Movie>();
            
            foreach (var movie in movies)
            {
                var dbMovie = dbMovies.FirstOrDefault(p => 
                    String.Equals(p.Path, movie.Path, StringComparison.CurrentCultureIgnoreCase));

                if (dbMovie == null)
                {
                    moviesToInsert.Add(movie);
                }
                else
                {           
                    moviesToUpdate.Add(movie.WithId(dbMovie.Id));
                }
            }

            await Task.WhenAll(_db.UpdateAllAsync(moviesToUpdate),
                               _db.InsertAllAsync(moviesToInsert));
        }

        public Task ApplyChanges(List<MovieWrapper> movies)
        {
            return ApplyChanges(Mapper.Map<List<Movie>>(movies));
        }

        public async Task<List<Movie>> GetAll()
        {
            return await _db.Table<Movie>().ToListAsync();
        }

        public async Task<List<MovieWrapper>> GetAllAsWrappers()
        {
            var movies = await _db.Table<Movie>().ToListAsync();
            return Mapper.Map<List<MovieWrapper>>(movies);
        }
    }
}

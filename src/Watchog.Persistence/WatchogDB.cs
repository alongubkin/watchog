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
    public sealed class WatchogDB
    {
        private readonly SQLiteAsyncConnection _db;

        static WatchogDB()
        {
            Mapper.CreateMap<MovieWrapper, Movie>();
            Mapper.CreateMap<Movie, MovieWrapper>()
                .ConstructUsing((Func<ResolutionContext, MovieWrapper>) (r => new MovieWrapper()));
        }

        public WatchogDB(string path)
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
                    moviesToInsert.Add(movie.UpdatedNow());
                }
                else if (dbMovie.State != movie.State)
                {
                    moviesToUpdate.Add(movie.UpdatedNow().WithId(dbMovie.Id));
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
            return Mapper.Map<List<MovieWrapper>>(await GetAll());
        }

        public async Task<List<Movie>> GetRecentlyWatched(int page, int moviesInPage = 10)
        {
            return await _db.Table<Movie>()
                .Where(movie => movie.State == MovieState.Watched)
                .OrderByDescending(movie => movie.UpdateDate)
                .Skip(page*moviesInPage)
                .Take(moviesInPage)
                .ToListAsync();
        }
    }
}

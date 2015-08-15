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
        private readonly SQLiteConnection _db;

        static Database()
        {
            Mapper.CreateMap<MovieWrapper, Movie>();
        }

        public Database(string path)
        {
            _db = new SQLiteConnection(path);
            _db.CreateTable<Movie>();
        }

        public void ApplyChanges(List<Movie> movies)
        {
            throw new NotImplementedException();
        }

        public void ApplyChanges(List<MovieWrapper> movies)
        {
            ApplyChanges(Mapper.Map<List<Movie>>(movies));
        }

        public List<Movie> GetAll()
        {
            throw new NotImplementedException();
        } 
    }
}

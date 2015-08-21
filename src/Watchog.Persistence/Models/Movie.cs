using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SQLite;
using Watchog.IPC;

namespace Watchog.Persistence.Models
{
    public class Movie
    {
        [PrimaryKey, AutoIncrement]
        public int Id { get; set; }

        [MaxLength(260)]
        public string Path { get; set; }

        public MovieState State { get; set; }

        public Movie WithId(int id)
        {
            this.Id = id;
            return this;
        }
    }
}

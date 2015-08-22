using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SQLite;
using Watchog.IPC;

namespace Watchog.Persistence.Models
{
    public sealed class Movie
    {
        [PrimaryKey, AutoIncrement]
        public int Id { get; set; }

        [MaxLength(260)]
        public string Path { get; set; }

        public MovieState State { get; set; }

        public DateTime UpdateDate { get; set; }

        [Ignore]
        public string Name => System.IO.Path.GetFileNameWithoutExtension(Path);

        public Movie WithId(int id)
        {
            this.Id = id;
            return this;
        }

        public Movie UpdatedNow()
        {
            UpdateDate = DateTime.UtcNow;
            return this;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tracko.IPC;
using System.Threading;

namespace Tracko.Test
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var server = new IPCPeer())
            {
                server.SetMovieState(@"D:\TV\The.Flash.2014.S01E02.HDTV.x264-LOL.mp4", 
                    MovieState.Watched);
                server.SetMovieState(@"D:\TV\Game.of.Thrones.S05E04.HDTV.x264-Xclusive4iPT.mp4",
                    MovieState.Watched);
                Console.WriteLine(server.GetMovieState(@"D:\TV\The.Flash.2014.S01E02.HDTV.x264-LOL.mp4"));
                Console.ReadLine();
            }
        }
    }
}

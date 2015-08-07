using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tracko.IPC.CLRBridge;
using System.Threading;

namespace Tracko.Test
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var server = new IPCServer())
            {
                server.SetMovieState("Test", MovieState.Watched);
                Console.WriteLine(server.GetMovieState("Test"));
            }
        }
    }
}

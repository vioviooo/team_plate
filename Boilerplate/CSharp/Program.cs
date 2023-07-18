using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Reflection;

namespace ConsoleApp1
{
    internal class Program
    {
        static void solve(StreamReader sr, StreamWriter sw){
            //let's go kid
        }
        static void Main(string[] args)
        {
            Stopwatch speedTest = new Stopwatch(); 

            string curDir = AppDomain.CurrentDomain.BaseDirectory;
            StreamReader sr = new StreamReader(curDir + @"\input.txt");
            StreamWriter sw = new StreamWriter(curDir + @"\output.txt");

            speedTest.Start();
            solve(sr,sw);
            speedTest.Stop();

            sw.WriteLine("Process finished in : {0}.{1}",
                speedTest.Elapsed.Seconds, speedTest.Elapsed.Milliseconds);

            sr.Close();
            sw.Close();
        }
    }
}

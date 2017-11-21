namespace TestApplication
{
    using System;
    using System.Threading;
    using System.Threading.Tasks;

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("This is sample application.");
            Console.WriteLine("It will execute a Garbage Collection every 2 seconds, until you press a key.");
            Console.WriteLine();

            Task.Factory.StartNew(() =>
            {
                while (true)
                {
                    Thread.Sleep(2000);
                    GC.Collect();
                }
            });

            Console.ReadKey();
        }
    }
}

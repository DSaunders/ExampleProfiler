namespace TestApplication
{
    using System;
    using System.Threading;

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Looping. Press the enter key stop.");

            do
            {
                while (!Console.KeyAvailable)
                {
                    Thread.Sleep(200);
                }
            } while (Console.ReadKey(true).Key != ConsoleKey.Enter);
        }
    }
}

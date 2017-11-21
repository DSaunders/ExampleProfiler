namespace TestApplication
{
    using System;
    using System.Threading;

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("This is sample application. Press the enter key quit.");

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

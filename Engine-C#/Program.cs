﻿using BGD;

internal class Program
{
    private static void Main(string[] args)
    {
        Console.WriteLine("Press ESC key to close window");
        new Game().Run();
        Console.WriteLine("All done");
    }
}
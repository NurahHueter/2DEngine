using GGD_Template.GameObjects;
using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace BGD;


internal class Game
{
    public const int WIDTH = 640;

    public const int HEIGHT = 480;

    private const string TITLE = "GrundlagenGameDev";

    private readonly Color BG_COLOR = new(50, 50, 50);

    private readonly Clock clock = new();

    private readonly VideoMode mode = new(WIDTH, HEIGHT);

    private readonly RenderWindow window;

    private List<GameObject> gameObjects = new();

    private Player player;

    public Game()
    {
        window = new RenderWindow(mode, TITLE);

        window.SetVerticalSyncEnabled(true);

        // this is called lambda expression ( anonymous/nameless function)
        window.Closed += (sender, args) => { window.Close(); };

        // the same functionality but without lambda
        window.KeyPressed += CloseGame;
    }

    private void CloseGame(object sender, KeyEventArgs e)
    {
        if (e.Code == Keyboard.Key.Escape) window?.Close();
    }

    private void Initialize()
    {
        // Setup Inputmanager
        InputManager.Instance.Init(window);

        DebugDraw.Instance.Initialize(window);

        gameObjects = new List<GameObject>();
        // Setup Player
        player = new Player();
        player.Position = new Vector2f(WIDTH / 2, HEIGHT / 2);
        gameObjects.Add(player);

        // Load Sound
        AssetManager.LoadSound("CompleteSound", @".\Assets\completeSound.wav");

        // Load Music
        AssetManager.LoadMusic("MusicTrack", @".\Assets\musicTrack.ogg");

        // Play Music
        AssetManager.Music["MusicTrack"].Play();

        // init all GameObjects
        foreach (var gameObject in gameObjects) gameObject.Initialize();
    }
    
    public void Run()
    {
        Initialize();

        while (window.IsOpen)
        {
            var deltaTime = clock.Restart().AsSeconds();

            HandleEvents();
            Update(deltaTime);
            Draw();
        }
    }

    private void HandleEvents()
    {
        window.DispatchEvents();
    }

    private void Draw()
    {
        window.Clear(BG_COLOR);

        DrawFloor(new Vector2f(0, 0),
            new Vector2i(10, 10),
            new Vector2i(64, 64));

        foreach (var gameObject in gameObjects)
            gameObject.Draw(window);

        //DrawLine(player.Position, new Vector2f(0, 0), Color.Green);
        // DrawRectangle(new Vector2f(300, 300), 100, 100, Color.Black);
        window.Display();
    }

    private void DrawFloor(
        Vector2f position,
        Vector2i tiles,
        Vector2i tileSize
    )
    {
        for (var x = 0; x < tiles.X; x++)
        for (var y = 0; y < tiles.Y; y++)
        {
            var tilepos =
                new Vector2f(position.X + x * tileSize.X,
                    position.Y + y * tileSize.Y);
            DebugDraw.Instance.DrawRectangle(tilepos,
                tileSize.X,
                tileSize.Y,
                (x + y) % 2 == 0 ? Color.White : Color.Black);
        }
    }


    private void Update(float deltaTime)
    {
        foreach (var gameObject in gameObjects)
            gameObject.Update(deltaTime);

        checkAreaBorders();

        // InputManager Update
        InputManager.Instance.update();
    }

    private void checkAreaBorders()
    {
        var left = 0;
        var top = 0;
        var right = 640;
        var bottom = 480;

        if (player.Position.Y > bottom - player.CollisionRect.Height / 2)
            player.Position = new Vector2f(player.Position.X, bottom - player.CollisionRect.Height / 2);

        if (player.Position.Y < top + player.CollisionRect.Height / 2)
            player.Position = new Vector2f(player.Position.X, top + player.CollisionRect.Height / 2);

        if (player.Position.X > right - player.CollisionRect.Width / 2)
            player.Position = new Vector2f(right - player.CollisionRect.Width / 2, player.Position.Y);

        if (player.Position.X < left + player.CollisionRect.Width / 2)
            player.Position = new Vector2f(left + player.CollisionRect.Width / 2, player.Position.Y);
    }

    private void RespawnPlayer()
    {
        player.Position = new Vector2f(WIDTH / 2, HEIGHT / 2);
    }
}
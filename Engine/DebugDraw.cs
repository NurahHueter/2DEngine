using SFML.Graphics;
using SFML.System;

internal class DebugDraw
{
    private static DebugDraw? _instance;

    private RenderWindow window;

    public static DebugDraw Instance
    {
        get { return _instance ??= new DebugDraw(); }
    }

    public void Initialize(RenderWindow renderWindow)
    {
        this.window = renderWindow;
    }

    public void DrawLine(Vector2f startPoint, Vector2f endPoint, Color color)
    {
        var line =
            new Vertex[]
            {
                new(startPoint, color),
                new(endPoint, color)
            };
        window.Draw(line, 0, 2, PrimitiveType.Lines);
    }

    public void DrawRectOutline(Vector2f position, int width, int height, Color color)
    {
        var bottomLeftPos = new Vector2f(position.X, position.Y + height);
        var topLeftPos = new Vector2f(position.X, position.Y);
        var topRightPos = new Vector2f(position.X + width, position.Y);
        var bottomRightPos =
            new Vector2f(position.X + width, position.Y + height);

        var line = new Vertex[]
            {
                new(bottomLeftPos, color),
                new(topLeftPos, color)
            };
        window.Draw(line, 0, 2, PrimitiveType.Lines);

        line = new Vertex[]
            {
                new(topLeftPos, color),
                new(topRightPos, color)
            };
        window.Draw(line, 0, 2, PrimitiveType.Lines);

        line = new Vertex[]
            {
                new(topRightPos, color),
                new(bottomRightPos, color)
            };
        window.Draw(line, 0, 2, PrimitiveType.Lines);

        line = new Vertex[]
            {
                new(bottomRightPos, color),
                new(bottomLeftPos, color)
            };
        window.Draw(line, 0, 2, PrimitiveType.Lines);
    }

    public void DrawRectOutline(IntRect intRect, Color color)
    {
        var position = new Vector2f(intRect.Left, intRect.Top);
        var width = intRect.Width;
        var height = intRect.Height;

        var bottomLeftPos = new Vector2f(position.X, position.Y + height);
        var topLeftPos = new Vector2f(position.X, position.Y);
        var topRightPos = new Vector2f(position.X + width, position.Y);
        var bottomRightPos =
            new Vector2f(position.X + width, position.Y + height);

        var line = new Vertex[]
            {
                new(bottomLeftPos, color),
                new(topLeftPos, color)
            };
        window.Draw(line, 0, 2, PrimitiveType.Lines);

        line = new Vertex[]
            {
                new(topLeftPos, color),
                new(topRightPos, color)
            };
        window.Draw(line, 0, 2, PrimitiveType.Lines);

        line = new Vertex[]
            {
                new(topRightPos, color),
                new(bottomRightPos, color)
            };
        window.Draw(line, 0, 2, PrimitiveType.Lines);

        line = new Vertex[]
            {
                new(bottomRightPos, color),
                new(bottomLeftPos, color)
            };
        window.Draw(line, 0, 2, PrimitiveType.Lines);
    }

    public void DrawRectangle(Vector2f position, int width, int height, Color color)
    {
        var rectangle = new RectangleShape(new Vector2f(width, height));

        rectangle.Position = position;
        rectangle.FillColor = color;
        window.Draw(rectangle);
    }

    public void DrawRectangle(IntRect rect, Color color)
    {
        var rectangle =  new RectangleShape(new Vector2f(rect.Width, rect.Height));

        rectangle.Position = new Vector2f(rect.Left, rect.Top);
        rectangle.FillColor = color;
        window.Draw(rectangle);
    }
}
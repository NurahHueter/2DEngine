using BGD;
using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace GGD_Template.GameObjects;

internal class Player : GameObject
{
    private const float ANIMATION_SPEED = 8f;

    private const int TILING_X = 10;

    private const int TILING_Y = 8;
    private readonly Sprite animatedSprite;

    private readonly int[]
        animationTypeFramesCount = { 3, 3, 1, 3, 10, 10, 10, 10 };

    private const float MoveSpeed = 150.0f;

    private float animationTimeIndex;
    private readonly Vector2i colliderSize = new(50, 60);

    //Animation
    private Animationtype m_animationType = Animationtype.IdleDown;

    public Player()
    {
        AssetManager.LoadTexture("Character", @".\Assets\playerSpriteSheet.png");
        animatedSprite = new Sprite(AssetManager.Textures["Character"]);
    }


    public IntRect CollisionRect { get; private set; }

    public IntRect PlayerCollisionRect { get; private set; }

    public override void Draw(RenderWindow window)
    {
        DoAnimation();

        window.Draw(animatedSprite);

        DebugDraw.Instance.DrawRectOutline(
            new Vector2f(animatedSprite.GetGlobalBounds().Left, animatedSprite.GetGlobalBounds().Top),
            (int)animatedSprite.GetGlobalBounds().Width,
            (int)animatedSprite.GetGlobalBounds().Height,
            Color.Red);

        DebugDraw.Instance.DrawRectOutline(CollisionRect, Color.Green);
    }

    public override void Initialize()
    {
        animatedSprite.Scale = new Vector2f(1.0f, 1.0f);
        animatedSprite.Position = new Vector2f(0, 0);

        animatedSprite.TextureRect =
            new IntRect(0,
                0,
                animatedSprite.TextureRect.Width / TILING_X,
                animatedSprite.TextureRect.Height / TILING_Y);

        Origin = new Vector2f(animatedSprite.TextureRect.Width / 2f, animatedSprite.TextureRect.Height / 2f);

        UpdateTransform();
        UpdateCollider();
    }

    public override void Update(float deltaTime)
    {
        UpdateTransform();
        UpdateCollider();
        HandleIdle();

        HandleInput(deltaTime);

        // Update Animation Idx
        animationTimeIndex += deltaTime * ANIMATION_SPEED;

        // update playerCollisionRect
        PlayerCollisionRect =
            new IntRect((int)Position.X,
                (int)Position.Y,
                (int)animatedSprite.GetGlobalBounds().Width,
                (int)animatedSprite.GetGlobalBounds().Height);
    }

    private void UpdateTransform()
    {
        animatedSprite.Position = Position;
        animatedSprite.Rotation = Rotation;
        animatedSprite.Scale = Scale;
        animatedSprite.Origin = Origin;
    }

    private void UpdateCollider()
    {
        CollisionRect =
            new IntRect(
                (int)Position.X - colliderSize.X / 2,
                (int)Position.Y - colliderSize.Y / 2,
                colliderSize.X,
                colliderSize.Y);
    }

    private void HandleInput(float deltaTime)
    {
        //get input
        if (InputManager.Instance.GetKeyPressed(Keyboard.Key.W))
        {
            m_animationType = Animationtype.RunUp;
            Position -=
                new Vector2f(0, 1) * MoveSpeed * deltaTime;
        }

        if (InputManager.Instance.GetKeyPressed(Keyboard.Key.A))
        {
            m_animationType = Animationtype.RunLeft;
            Position -=
                new Vector2f(1, 0) * MoveSpeed * deltaTime;
        }

        if (InputManager.Instance.GetKeyPressed(Keyboard.Key.S))
        {
            m_animationType = Animationtype.RunDown;
            Position +=
                new Vector2f(0, 1) * MoveSpeed * deltaTime;
        }

        if (InputManager.Instance.GetKeyPressed(Keyboard.Key.D))
        {
            m_animationType = Animationtype.RunRight;
            Position +=
                new Vector2f(1, 0) * MoveSpeed * deltaTime;
        }
    }

    private void HandleIdle()
    {
        if (m_animationType == Animationtype.RunUp)
            m_animationType = Animationtype.IdleUp;
        if (m_animationType == Animationtype.RunDown)
            m_animationType = Animationtype.IdleDown;
        if (m_animationType == Animationtype.RunLeft)
            m_animationType = Animationtype.IdleLeft;
        if (m_animationType == Animationtype.RunRight)
            m_animationType = Animationtype.IdleRight;
    }

    private void DoAnimation()
    {
        var animationFrame = (int)animationTimeIndex % animationTypeFramesCount[(int)m_animationType];

        animatedSprite.TextureRect = new IntRect
        {
            Left = animationFrame * animatedSprite.TextureRect.Width,
            Top = (int)m_animationType * animatedSprite.TextureRect.Height,
            Width = animatedSprite.TextureRect.Width,
            Height = animatedSprite.TextureRect.Height
        };
    }
}
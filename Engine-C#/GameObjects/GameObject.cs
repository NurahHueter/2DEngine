using SFML.Graphics;

namespace GGD_Template.GameObjects;

internal abstract class GameObject : Transformable
{
    public abstract void Initialize();
    public abstract void Update(float deltaTime);
    public abstract void Draw(RenderWindow window);
}
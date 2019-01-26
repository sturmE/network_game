//
//  SFMLTypes.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include <SFML/Graphics.hpp>

using ConvexShapePtr = std::shared_ptr<sf::ConvexShape>;
using CircleShapePtr = std::shared_ptr<sf::CircleShape>;
using DrawablePtr = std::shared_ptr<sf::Drawable>;
using SpritePtr = std::shared_ptr<sf::Sprite>;
using TexturePtr = std::shared_ptr<sf::Texture>;

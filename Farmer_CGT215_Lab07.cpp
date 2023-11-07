// Farmer_CGT215_Lab07.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sfp;
using namespace sf;

int main() {
    // Create our window and world with gravity 0,1.
    RenderWindow window(VideoMode(800, 600), "Bounce");
    World world(Vector2f(0, 1));

    // Create the ball.
    PhysicsCircle ball;
    ball.setCenter(Vector2f(200, 100));
    ball.applyImpulse(Vector2f(0.3, 0));
    ball.setRadius(20);
    world.AddPhysicsBody(ball);

    // Create the floor.
    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);

    // Create the ceiling. 
    PhysicsRectangle ceiling;
    ceiling.setSize(Vector2f(800, 20));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true);
    world.AddPhysicsBody(ceiling);

    // Create the left wall.
    PhysicsRectangle leftWall;
    leftWall.setSize(Vector2f(20, 600));
    leftWall.setCenter(Vector2f(10, 300));
    leftWall.setStatic(true);
    world.AddPhysicsBody(leftWall);

    // Create the right wall.
    PhysicsRectangle rightWall;
    rightWall.setSize(Vector2f(20, 600));
    rightWall.setCenter(Vector2f(790, 300));
    rightWall.setStatic(true);
    world.AddPhysicsBody(rightWall);

    // Create center block.
    PhysicsRectangle centerBlock;
    centerBlock.setSize(Vector2f(60, 60));
    centerBlock.setCenter(Vector2f(400, 300));
    centerBlock.setStatic(true);
    world.AddPhysicsBody(centerBlock);

    // Counts the "thuds" when floor collision happens.
    int thudCount(0);
    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };

    // Counts the "thuds" when ceiling collision happens.
    ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };

    // Counts the "thuds" when left wall collision happens.
    leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };

    // Counts the "thuds" when right wall collision happens.
    rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };

    // Counts the "bangs" when the ball hits the center block.
    int bangCount(0);
    centerBlock.onCollision = [&bangCount, &centerBlock, &window](PhysicsBodyCollisionResult result) {
        bangCount++;
        cout << "Bang " << bangCount << endl;
        
        // Ends the code if ball hits the center block 3 times.
        if (bangCount == 3) {
            exit(0);
        }
    };

    Clock clock;
    Time lastTime(clock.getElapsedTime());
    while (true) {
        // Calculate MS since last frame.
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());
        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }

        // Create the frame.
        window.clear(Color(0, 0, 0));
        window.draw(ball);
        window.draw(floor);
        window.draw(ceiling);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(centerBlock);
        window.display();
    }
}
#include <box2d/box2d.h>
#include <raylib.h>

#include <iostream>

int main() {

    float posx=0;
    float posy=0;


    InitWindow(1000,1500,"Box2D Physics");
    SetTargetFPS(60);


// ⁡⁣⁢⁣𝗖𝗿𝗲𝗮𝘁𝗲 𝗮 𝘄𝗼𝗿𝗹𝗱.⁡
    b2WorldDef worldDef=b2DefaultWorldDef();
    worldDef.gravity=(b2Vec2){0.0f, -9.8f};

    b2WorldId worldId= b2CreateWorld(&worldDef);

// ⁡⁣⁢⁣𝗖𝗿𝗲𝗮𝘁𝗲 𝗮 𝗴𝗿𝗼𝘂𝗻𝗱 𝗯𝗼𝗱𝘆.⁡
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = (b2Vec2){0.0f, -10.0f};
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);

    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

// ⁡⁣⁢⁣⁡⁣⁢⁣𝗖𝗿𝗲𝗮𝘁𝗲 𝗮 𝗱𝘆𝗻𝗮𝗺𝗶𝗰 𝗯𝗼𝗱𝘆.⁡
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularVelocity=20.0f;
    bodyDef.position = (b2Vec2){0.0f, 20.0f};
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.0f;
    shapeDef.restitution = 0.4f;
    
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

 // ⁡⁣⁢⁣𝗦𝘁𝗮𝗿𝘁 𝘁𝗵𝗲 𝗦𝗶𝗺𝘂𝗹𝗮𝘁𝗶𝗼𝗻⁡

    float timeStep = 1.0f / 60.0f;
    int substepCount = 4;
    
while(!WindowShouldClose()) {
    // Step physics
    b2World_Step(worldId, timeStep, substepCount);

    // Get physics body position
    b2Vec2 position = b2Body_GetPosition(bodyId);
    b2Rot rotation = b2Body_GetRotation(bodyId);

    b2Vec2 positionGround =b2Body_GetPosition(groundId);


    // Convert meters to pixels
    float screenX = position.x * 50 + 500;
    float screenY = 1500 - (position.y * 50);

    // Drawing
    BeginDrawing();
    ClearBackground(WHITE);
    
    Rectangle myrect = {screenX, screenY, 50, 50};
    DrawRectanglePro(myrect, {25, 25}, b2Rot_GetAngle(rotation) * RAD2DEG, BLACK);

    DrawRectangle(0,1500-(positionGround.y*50),1000,1500-(positionGround.y*50+20),BLACK);


    DrawRectangle(0,1475,1000,5,BLACK);

    

    EndDrawing();
}

    b2DestroyWorld(worldId);
    std::cout << "Box2D is working!" << std::endl;
    return 0;
}

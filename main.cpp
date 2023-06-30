#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib>
#include <ctime>

float generateDirection();
void updateScores();
void waitForOneSecond();
void newGame(bool isLeft);
void clearKeyPressedState();
sf::Color getRandomColor();
bool checkCollision(const sf::CircleShape& ball, const sf::RectangleShape& line,int height);

sf::Text leftScore;
sf::Text rightScore;
int scLeft=0;
int scRight=0;
bool isStarted= false;
int main() {

   sf::RenderWindow window(sf::VideoMode(2000,1200),"PONG",sf::Style::Close);
    sf::Font font;
    if (!font.loadFromFile("04B_30__.TTF")){
        std::cout<<"ERROR FONT"<<std::endl;
    };
    float characterSizeRatio = window.getSize().y / 10.0f;
    leftScore.setFont(font);
    rightScore.setFont(font);
    updateScores();
    sf::Event event;
    float numbersPositionY=window.getSize().y/20;
    float nuberLeftX=window.getSize().x/10*3;
    float nuberRightX=window.getSize().x/10*6;
    float leftDy=0;
    float rightDy=0;
    float ballDx=0;
    float ballDy=0;
    float lineSpeed=3.0;
    float ballRadius=window.getSize().x/80;
    float ballCenterX=window.getSize().x/2-ballRadius;
    float ballCenterY=window.getSize().y/2-ballRadius;
    float lineHeight= window.getSize().y/5;
    float centerY=window.getSize().y/2-lineHeight/2;
    float centerLeftX=window.getSize().x/10;
    float centerRightX=window.getSize().x/10*8;
    float lineWidth=window.getSize().x/40;

    sf::CircleShape ball(ballRadius);
   sf::RectangleShape leftLine(sf::Vector2f(lineWidth,lineHeight));
   sf::RectangleShape rightLine(sf::Vector2f(lineWidth,lineHeight));
    ball.setPosition(sf::Vector2f(ballCenterX,ballCenterY));
   leftLine.setPosition(sf::Vector2f(centerLeftX,centerY));
   rightLine.setPosition(sf::Vector2f(centerRightX,centerY));
   leftScore.setPosition(sf::Vector2f(nuberLeftX,numbersPositionY));
   rightScore.setPosition(sf::Vector2f(nuberRightX,numbersPositionY));
   leftScore.setCharacterSize(characterSizeRatio);
   rightScore.setCharacterSize(characterSizeRatio);
   while (window.isOpen()){
       window.clear();
       while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){window.close();}
            if (!isStarted  && event.type == sf::Event::KeyPressed) {
                isStarted= true;
                ballDy= generateDirection();
                ballDx= generateDirection();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                leftDy=-lineSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                leftDy=lineSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                rightDy=-lineSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                rightDy=lineSpeed;
            }
            if (event.type==sf::Event::KeyReleased){
                if (event.key.code==sf::Keyboard::W ||event.key.code==sf::Keyboard::S){
                    leftDy=0;
                }
                if (event.key.code==sf::Keyboard::Up ||event.key.code==sf::Keyboard::Down){
                    rightDy=0;
                }
            }
        }
        if (leftLine.getPosition().y+leftDy==0 || leftLine.getPosition().y+leftDy==window.getSize().y-leftLine.getSize().y){
            leftDy=0;
        }
       if (rightLine.getPosition().y+rightDy==0 || rightLine.getPosition().y+rightDy==window.getSize().y-rightLine.getSize().y){
           rightDy=0;
       }
       if (ball.getPosition().y <= 0 || ball.getPosition().y >= window.getSize().y - ball.getRadius()) {
           ballDy *= -1;
       }
        //left line upper part
       if (((leftLine.getPosition().y<ball.getPosition().y && ball.getPosition().y<=leftLine.getPosition().y+lineHeight/2)&& (leftLine.getPosition().x<ball.getPosition().x&&ball.getPosition().x<leftLine.getPosition().x+lineWidth))){
           ballDy=-1*std::abs(ballDy);
           ballDx*=-1;
           ball.setFillColor(getRandomColor());
       }
       //right line upper part
       if ((rightLine.getPosition().y<ball.getPosition().y && ball.getPosition().y<=rightLine.getPosition().y+lineHeight/2)&&(rightLine.getPosition().x<ball.getPosition().x&&ball.getPosition().x<rightLine.getPosition().x+lineWidth)){
           ballDy=-1*std::abs(ballDy);
           ballDx*=-1;
           ball.setFillColor(getRandomColor());
       }
       //left line bottom part
       if (((leftLine.getPosition().y+lineHeight/2<ball.getPosition().y && ball.getPosition().y<leftLine.getPosition().y+lineHeight)&& (leftLine.getPosition().x<ball.getPosition().x&&ball.getPosition().x<leftLine.getPosition().x+lineWidth))){
           ballDy=std::abs(ballDy);
           ballDx*=-1;
           ball.setFillColor(getRandomColor());
       }
       //right line bottom part
       if ((rightLine.getPosition().y+lineHeight/2<ball.getPosition().y && ball.getPosition().y<rightLine.getPosition().y+lineHeight)&&(rightLine.getPosition().x<ball.getPosition().x&&ball.getPosition().x<rightLine.getPosition().x+lineWidth)){
           ballDy=std::abs(ballDy);
           ballDx*=-1;
           ball.setFillColor(getRandomColor());
       }

       if (ball.getPosition().x<0-ball.getRadius()*2){
           isStarted= false;
           ballDx=0;
           ballDy=0;
           leftLine.setPosition(sf::Vector2f(centerLeftX,centerY));
           rightLine.setPosition(sf::Vector2f(centerRightX,centerY));
           ball.setPosition(sf::Vector2f(ballCenterX,ballCenterY));
           newGame(false);
       }
       if (ball.getPosition().x>window.getSize().x){
           isStarted= false;
           ballDx=0;
           ballDy=0;
           leftLine.setPosition(sf::Vector2f(centerLeftX,centerY));
           rightLine.setPosition(sf::Vector2f(centerRightX,centerY));
           ball.setPosition(sf::Vector2f(ballCenterX,ballCenterY));
           newGame(true);
       }
        ball.move(sf::Vector2f(ballDx,ballDy));
        rightLine.move(sf::Vector2f(0,rightDy));
        leftLine.move(sf::Vector2f(0,leftDy));
        window.draw(leftScore);
        window.draw(rightScore);
        window.draw(ball);
        window.draw(leftLine);
        window.draw(rightLine);
        window.display();
   }
}
void newGame(bool isLeft){
    if (isLeft){
        scLeft++;
    }else{
        scRight++;
    }
    updateScores();
    waitForOneSecond();
    clearKeyPressedState();
    isStarted= false;
}
float generateDirection() {
    return std::rand()%2==0? 1.5:-1.5;
}

void updateScores(){
    leftScore.setString(std::to_string(scLeft));
    rightScore.setString(std::to_string(scRight));
}
void waitForOneSecond() {
    sf::sleep(sf::seconds(1));
}
void clearKeyPressedState() {
    for (int key = 0; key < sf::Keyboard::KeyCount; ++key) {
        sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
    }
}
sf::Color getRandomColor(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int r = std::rand() % 128 + 128;
    int g = std::rand() % 128 + 128;
    int b = std::rand() % 128 + 128;
    return sf::Color(r, g, b);
}
bool checkCollision(const sf::CircleShape& ball, const sf::RectangleShape& line,int height){
    int ballX = static_cast<int>(ball.getPosition().x);
    if (ballX==line.getPosition().x && (ball.getPosition().y>line.getPosition().y && ball.getPosition().y<line.getPosition().y+height)){
        return true;
    }else{
        return false;
    }
}
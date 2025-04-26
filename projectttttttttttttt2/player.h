#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player();

    int getPosition() const;
    void setPosition(int position);
    void move(int steps);

private:
    int position;
};

#endif // PLAYER_H

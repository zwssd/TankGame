#ifndef SETTINGS_H
#define SETTINGS_H
/*
 * 此处为声明
 * 请查看Settings.cpp文件
 *
 * */
class Settings{
public:
    static int blockLength;
    static int bulletSize;
    static int bulletSpeed;
    static int life;
    static int width;
    static int height;
    static int tankSize;
    static int tankSpeed;
    static int bulletRadius;
    static int allEnemy;
    static unsigned int maxExist;
public:
    Settings()=delete;
};

#endif // SETTINGS_H

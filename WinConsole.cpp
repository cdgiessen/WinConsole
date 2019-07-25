#include "WinConsole.h"

namespace wc {

short toLinearInd(short x, short y, int width) { return y * width + x; }

Vec3::Vec3() {
  x = 0;
  y = 0;
  z = 0;
}

Vec3::Vec3(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vec3 Vec3::add(Vec3 other) {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::sub(Vec3 other) {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::mult(Vec3 other) {
  return Vec3(x * other.x, y * other.y, z * other.z);
}

Vec3 Vec3::div(Vec3 other) {
  return Vec3(x / other.x, y / other.y, z / other.z);
}

float Vec3::getIndex(short ind) {
  switch (ind) {
  case 0:
    return x;
    break;
  case 1:
    return y;
    break;
  case 2:
    return z;
    break;
  default:
    return 1.0f;
    break;
  }
}

void Vec3::setIndex(float n, short ind) {
  switch (ind) {
  case 0:
    x = n;
    break;
  case 1:
    y = n;
    break;
  case 2:
    z = n;
    break;
  }
}

Vec3 Vec3::integer() { return Vec3(floor(x), floor(y), floor(z)); }

Mat3::Mat3() { *this = Mat3(0.0f); }

Mat3::Mat3(float d) {
  for (short x = 0; x < MAT_SIZE; x++) {
    for (short y = 0; y < MAT_SIZE; y++) {
      dat[x][y] = 0.0f;
    }
  }
  dat[0][0] = d;
  dat[1][1] = d;
  dat[2][2] = d;
}

Mat3::~Mat3() {
  // for(short i = 0; i < MAT_SIZE; i++)
  //	delete[] dat[i];
  // delete[] dat;
}

Mat3 Mat3::add(Mat3 other) {
  Mat3 res(0.0f);
  for (short x = 0; x < MAT_SIZE; x++) {
    for (short y = 0; y < MAT_SIZE; y++) {
      res.dat[x][y] = dat[x][y] + other.dat[x][y];
    }
  }
  return res;
}

Mat3 Mat3::sub(Mat3 other) {
  Mat3 res(0.0f);
  for (short x = 0; x < MAT_SIZE; x++) {
    for (short y = 0; y < MAT_SIZE; y++) {
      res.dat[x][y] = dat[x][y] - other.dat[x][y];
    }
  }
  return res;
}

Mat3 Mat3::mult(Mat3 other) {
  Mat3 res(0.0f);
  for (short x = 0; x < MAT_SIZE; x++) {
    for (short y = 0; y < MAT_SIZE; y++) {
      res.dat[x][y] = dat[x][0] * other.dat[0][y] +
                      dat[x][1] * other.dat[1][y] + dat[x][2] * other.dat[2][y];
    }
  }
  return res;
}

Mat3 Mat3::integer() {
  Mat3 res(0.0f);
  for (short x = 0; x < MAT_SIZE; x++) {
    for (short y = 0; y < MAT_SIZE; y++) {
      res.dat[x][y] = floor(dat[x][y]);
    }
  }
  return res;
}

Vec3 VecTimesMat(Vec3 vec, Mat3 mat) {
  return Vec3((vec.x * mat.dat[0][0]) + (vec.y * mat.dat[0][1]) +
                  (vec.z * mat.dat[0][2]),
              (vec.x * mat.dat[1][0]) + (vec.y * mat.dat[1][1]) +
                  (vec.z * mat.dat[1][2]),
              (vec.x * mat.dat[2][0]) + (vec.y * mat.dat[2][1]) +
                  (vec.z * mat.dat[2][2]));
}

Vec3 VecTimesMat(Mat3 mat, Vec3 vec) {
  return Vec3((vec.x * mat.dat[0][0]) + (vec.y * mat.dat[1][0]) +
                  (vec.z * mat.dat[2][0]),
              (vec.x * mat.dat[0][1]) + (vec.y * mat.dat[1][1]) +
                  (vec.z * mat.dat[2][1]),
              (vec.x * mat.dat[0][2]) + (vec.y * mat.dat[1][2]) +
                  (vec.z * mat.dat[2][2]));
}

void printVec(Vec3 o) { printf("%.2f %.2f %.2f", o.x, o.y, o.z); }

void printMat(Mat3 o) {
  for (short x = 0; x < Mat3::MAT_SIZE; x++) {
    for (short y = 0; y < Mat3::MAT_SIZE; y++) {
      printf("%.2f%s", o.dat[x][y], (y == 2 ? "\n" : " "));
    }
  }
}

void overrideAsRandom(Vec3 &vec, float min, float max) {
  vec.x = (float)(rand()) / (float)(RAND_MAX) * (max - min) + min;
  vec.y = (float)(rand()) / (float)(RAND_MAX) * (max - min) + min;
  vec.z = (float)(rand()) / (float)(RAND_MAX) * (max - min) + min;
}

void overrideAsRandom(Mat3 &mat, float min, float max) {
  for (short x = 0; x < Mat3::MAT_SIZE; x++) {
    for (short y = 0; y < Mat3::MAT_SIZE; y++) {
      mat.dat[x][y] = (float)(rand()) / (float)(RAND_MAX) * (max - min) + min;
    }
  }
}

Map::Map() {
  width = 7;
  height = 7;
  for (short y = 0; y < height; y++) {
    dat.push_back(new char[width]);
    for (short x = 0; x < width; x++) {
      dat[y][x] = '#';
    }
  }
}

Map::Map(short width, short height) {
  this->width = width;
  this->height = height;
  for (short y = 0; y < height; y++) {
    dat.push_back(new char[width]);
    for (short x = 0; x < width; x++) {
      dat[y][x] = '#';
    }
  }
}

Map::Map(short width, short height, std::vector<char *> dat) {
  this->width = width;
  this->height = height;
  this->dat = dat;
}

Map::~Map() { dat.clear(); }

WinConsole::~WinConsole() {
  delete[] buffer;
  delete[] keys;
}

bool WinConsole::build(short width, short height, short fontw, short fonth) {
  this->width = width;
  this->height = height;
  this->fontw = fontw;
  this->fonth = fonth;
  alive = false;
  buffer = new char[width * height];
  for (unsigned short i = 0; i < width * height; i++)
    buffer[i] = ' ';
  keys = new bool[KEYS_LENGTH];
  for (unsigned short i = 0; i < KEYS_LENGTH; i++)
    keys[i] = false;
  translation = Mat3(1.0f);
  rotation = Mat3(1.0f);
  scalar = Mat3(1.0f);
  transform = translation.mult(rotation.mult(scalar));
  return systemSetup();
}

bool WinConsole::systemSetup() {
#ifdef _WIN32 // WINDOWS MACHINES
  hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                       CONSOLE_TEXTMODE_BUFFER, NULL);
  SetConsoleActiveScreenBuffer(hConsole);
  junk = 0;

  winsize = {0, 0, 1, 1};
  if (!SetConsoleWindowInfo(hConsole, TRUE, &winsize))
    return false;

  COORD coord = {(short)(width), (short)(height)};
  if (!SetConsoleScreenBufferSize(hConsole, coord))
    return false;

  CONSOLE_FONT_INFOEX cfi;
  cfi.cbSize = sizeof(cfi);
  cfi.nFont = 0;
  cfi.dwFontSize.X = fontw;
  cfi.dwFontSize.Y = fonth;
  cfi.FontFamily = FF_DONTCARE;
  cfi.FontWeight = FW_NORMAL;
  SetCurrentConsoleFontEx(hConsole, false, &cfi);

  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    return false;
  if ((short)(width) > csbi.dwMaximumWindowSize.Y)
    return false;
  if ((short)(height) > csbi.dwMaximumWindowSize.X)
    return false;

  winsize = {0, 0, (short)(width - 1), (short)(height - 1)};
  SetConsoleWindowInfo(hConsole, TRUE, &winsize);
#endif

#ifdef __linux__
  initscr();
  keypad(stdscr, TRUE);
  // raw();
  nodelay(stdscr, TRUE);

  // int x, y;
  // getyx(stdscr, y, x);

  win = newwin(height, width, 0, 0);
  keypad(win, TRUE);
  // raw();
  nodelay(win, TRUE);

#endif

  return true;
}

bool WinConsole::systemCleanup() {

#ifdef __linux__
  delwin(win);
  endwin();
#endif

  return true;
}

bool WinConsole::start() {
  if (!init())
    return false;
  alive = true;

  auto old = std::chrono::system_clock::now();
  auto cur = std::chrono::system_clock::now();

  while (alive) {

    cur = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedtime = cur - old;
    old = cur;
    elapsed = elapsedtime.count();

    for (unsigned short i = 0; i < width * height; i++)
      buffer[i] = ' ';

    update_inputs();

    if (!tick(elapsed))
      alive = false;
    if (!render())
      alive = false;

    update_screen();
  }
  systemCleanup();
  return true;
}

bool WinConsole::init() { return false; }

bool WinConsole::tick(float elapsed) { return false; }

bool WinConsole::render() { return false; }

void WinConsole::putChar(short x, short y, char c) {
  if (x > width - 1 || y > height - 1 || y * width + x > width * height - 1)
    return;
  Vec3 point = VecTimesMat(Vec3(x, y, 1.0f), transform).integer();
  if (pointInBounds(point))
    buffer[toLinearInd(point.x, point.y, width)] = c;
}

void WinConsole::stringAt(short x, short y, std::string str) {
  if (x >= 0 && y >= 0)
    sprintf(&buffer[toLinearInd(x, y, width)], "%s", str.c_str());
}

void WinConsole::drawRect(short x, short y, short w, short h, char c) {}

void WinConsole::fillRect(short x, short y, short w, short h, char c) {
  for (short xp = x; xp < x + w; xp++) {
    for (short yp = y; yp < y + h; yp++) {
      Vec3 point = VecTimesMat(Vec3(xp, yp, 1.0f), transform).integer();
      if (pointInBounds(point))
        buffer[toLinearInd(point.x, point.y, width)] = c;
    }
  }
}

void WinConsole::drawMap(short x, short y, Map map, bool spaceistransparent) {
  short xput = 0, yput = 0;
  for (short xx = x; xx < x + map.width; xx++) {
    for (short yy = y; yy < y + map.height; yy++) {
      Vec3 point = VecTimesMat(Vec3(xx, yy, 1.0f), transform).integer();
      if (pointInBounds(point)) {
        if (spaceistransparent) {
          if (map.dat[yput][xput] != ' ')
            buffer[toLinearInd(point.x, point.y, width)] = map.dat[yput][xput];
        } else
          buffer[toLinearInd(point.x, point.y, width)] = map.dat[yput][xput];
      }
      yput++;
    }
    yput = 0;
    xput++;
  }
}

void WinConsole::translate(float x, float y) {
  Mat3 newtranslation = Mat3(1.0f);
  newtranslation.dat[0][2] = x;
  newtranslation.dat[1][2] = y;
  translation = translation.mult(newtranslation);
  // translation = newtranslation;
}

void WinConsole::rotate(float rads) {
  Mat3 newrotation = Mat3(1.0f);
  newrotation.dat[0][0] = cos(rads);
  newrotation.dat[1][0] = -sin(rads);
  newrotation.dat[0][1] = sin(rads);
  newrotation.dat[1][1] = cos(rads);
  rotation = rotation.mult(newrotation);
  // rotation = newrotation;
}

void WinConsole::scale(float x, float y) {
  Mat3 newscalar = Mat3(1.0f);
  newscalar.dat[0][0] = x;
  newscalar.dat[1][1] = y;
  scalar = scalar.mult(newscalar);
  // scalar = newscalar;
}

void WinConsole::updateTransform() {
  transform = translation.mult(rotation.mult(scalar));
}

void WinConsole::resetTransform() {
  translation = Mat3(1.0f);
  rotation = Mat3(1.0f);
  scalar = Mat3(1.0f);
  transform = Mat3(1.0f);
}

bool WinConsole::pointInBounds(Vec3 point) {
  return (point.x >= 0 && point.y >= 0 && point.x < width && point.y < height &&
          toLinearInd(point.x, point.y, width) < width * height);
}

void WinConsole::setWidth(short width) { this->width = width; }

void WinConsole::setHeight(short height) { this->height = height; }

void WinConsole::setFontWidth(short fontw) { this->fontw = fontw; }

void WinConsole::setFontHeight(short fonth) { this->fonth = fonth; }

char *WinConsole::getBuffer() { return buffer; }

unsigned short WinConsole::getWidth() { return width; }

unsigned short WinConsole::getHeight() { return height; }

unsigned short WinConsole::getFontWidth() { return fontw; }

unsigned short WinConsole::getFontHeight() { return fonth; }

float WinConsole::getElapsed() { return elapsed; }

Mat3 &WinConsole::getTranslation() { return translation; }

Mat3 &WinConsole::getRotation() { return rotation; }

Mat3 &WinConsole::getScalar() { return scalar; }

Mat3 &WinConsole::getTransform() { return transform; }

bool WinConsole::getKey(unsigned short k) {
  if (k > KEYS_LENGTH)
    return false;
  return keys[k];
}

bool WinConsole::getKey(char k) { return keys[(unsigned short)(k)]; }

void WinConsole::update_inputs() {
#ifdef _WIN32
  for (unsigned short i = 0; i < KEYS_LENGTH; i++) {
    keys[i] = GetAsyncKeyState(i);
  }
#endif

#ifdef __linux__
  for (unsigned short i = 0; i < KEYS_LENGTH; i++) {
    keys[i] = false;
  }
  // noecho();
  int ch;
  while ((ch = wgetch(win)) != ERR) {
    keys[ch] = true;
  }
#endif
}

void WinConsole::update_screen() {

#ifdef _WIN32
  buffer[width * height - 1] = '\0';
  WriteConsoleOutputCharacter(hConsole, buffer, width * height, {0, 0}, &junk);
#endif

#ifdef __linux__

  buffer[width * height - 1] = '\0';
  wclear(win);
  for (short i = 0; i <= width; ++i) {
    for (short j = 0; j <= height; ++j) {
      // mvwprintw(win, j, i, "%c", buffer[i * width + j]);
      waddch(win, buffer[i * width + j]);
      //      mvaddch(j, i, buffer[i * width + j]);
    }
  }
  wrefresh(win);
#endif
}
} // namespace wc

#ifndef BASECLASS_H
#define BASECLASS_H

#include <QtGui/QStandardItem>
#include <string>

namespace Origin {
enum Origin {
  None = -1,
  TikTok = 0,
  Reels = 1,
  YoutubeShorts = 2,
};
}

namespace MemeTier {
enum MemeTier {
  None = -1,
  SkibidiOhioRizzler = 0,
  Sigma = 1,
  Based = 2,
  Cringe = 3
};
}

class BaseClass : public QStandardItem {
public:
  BaseClass() : QStandardItem("New Subject") { setMemeTier(memeTier); }
  virtual void setupSpecializedUi(QWidget *);
  virtual void setSpecializedNumber(QString, int);
  virtual void read(QDataStream &);
  virtual void write(QDataStream &) const;
  MemeTier::MemeTier getMemeTier() const;
  void setMemeTier(MemeTier::MemeTier);
  void setUserData();

public:
  int likes = 0;
  int comments = 0;
  QByteArray encodedImage;

private:
  MemeTier::MemeTier memeTier = MemeTier::None;
};

#endif // BASECLASS_H

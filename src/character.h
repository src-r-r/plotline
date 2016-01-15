#ifndef CHARACTER_H
#define CHARACTER_H


class Character : public QObject
{
    Q_OBJECT

private:
    QString
        *name,
        *nickname,
        *role,
        *label;

    QLinkedList<TraitCategories> *traitCategories;

public:
    explicit Character(QObject *parent = 0);

signals:

public slots:
};

#endif // CHARACTER_H

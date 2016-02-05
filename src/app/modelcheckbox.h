#ifndef MODELCHECKBOX_H
#define MODELCHECKBOX_H

#include <QCheckBox>
#include <QtCore>

class ModelCheckbox : public QCheckBox
{
    Q_OBJECT
public:
    explicit ModelCheckbox(const QString &label, const QVariant &value,
                           QWidget *parent = 0);

    QVariant value() const;
    void setValue(const QVariant &value);

signals:

    void toggled(bool checked, QVariant value);

public slots:

private:
    QVariant mValue;

private slots:
    void onToggled(bool checked);
};

#endif // MODELCHECKBOX_H

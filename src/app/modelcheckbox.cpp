#include "modelcheckbox.h"

ModelCheckbox::ModelCheckbox(const QString &label, const QVariant &value,
                             QWidget *parent) : QCheckBox(label, parent)
{
    mValue = value;
    connect(this, SIGNAL(toggled(bool)),
            this, SLOT(onToggled(bool)));
}

QVariant ModelCheckbox::value() const
{
    return mValue;
}

void ModelCheckbox::setValue(const QVariant &value)
{
    mValue = value;
}

void ModelCheckbox::onToggled(bool checked)
{
    emit toggled(checked, mValue);
}


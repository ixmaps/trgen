/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created: Wed Nov 17 18:31:36 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_aboutDialog
{
public:
    QDialogButtonBox *closeButton;
    QLabel *label;

    void setupUi(QDialog *aboutDialog)
    {
        if (aboutDialog->objectName().isEmpty())
            aboutDialog->setObjectName(QString::fromUtf8("aboutDialog"));
        aboutDialog->resize(400, 300);
        closeButton = new QDialogButtonBox(aboutDialog);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(30, 240, 341, 32));
        closeButton->setOrientation(Qt::Horizontal);
        closeButton->setStandardButtons(QDialogButtonBox::Close);
        closeButton->setCenterButtons(true);
        label = new QLabel(aboutDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 20, 201, 21));

        retranslateUi(aboutDialog);
        QObject::connect(closeButton, SIGNAL(accepted()), aboutDialog, SLOT(accept()));
        QObject::connect(closeButton, SIGNAL(rejected()), aboutDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(aboutDialog);
    } // setupUi

    void retranslateUi(QDialog *aboutDialog)
    {
        aboutDialog->setWindowTitle(QApplication::translate("aboutDialog", "About Traceroute Generator", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("aboutDialog", "Traceroute Generator", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class aboutDialog: public Ui_aboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H

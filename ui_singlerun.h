/********************************************************************************
** Form generated from reading UI file 'singlerun.ui'
**
** Created: Wed Nov 17 18:31:36 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLERUN_H
#define UI_SINGLERUN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SingleRunDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *hostNameEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SingleRunDialog)
    {
        if (SingleRunDialog->objectName().isEmpty())
            SingleRunDialog->setObjectName(QString::fromUtf8("SingleRunDialog"));
        SingleRunDialog->resize(611, 194);
        verticalLayout = new QVBoxLayout(SingleRunDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(SingleRunDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        hostNameEdit = new QLineEdit(SingleRunDialog);
        hostNameEdit->setObjectName(QString::fromUtf8("hostNameEdit"));

        horizontalLayout_2->addWidget(hostNameEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(17, 373, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(533, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(SingleRunDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(SingleRunDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SingleRunDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SingleRunDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SingleRunDialog);
    } // setupUi

    void retranslateUi(QDialog *SingleRunDialog)
    {
        SingleRunDialog->setWindowTitle(QApplication::translate("SingleRunDialog", "Traceroute Initiation", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SingleRunDialog", "Host", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SingleRunDialog: public Ui_SingleRunDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLERUN_H

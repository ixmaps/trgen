/********************************************************************************
** Form generated from reading UI file 'batchrun.ui'
**
** Created: Wed Nov 17 18:31:36 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATCHRUN_H
#define UI_BATCHRUN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BatchRunDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *trSetBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *BatchRunDialog)
    {
        if (BatchRunDialog->objectName().isEmpty())
            BatchRunDialog->setObjectName(QString::fromUtf8("BatchRunDialog"));
        BatchRunDialog->resize(611, 149);
        verticalLayout = new QVBoxLayout(BatchRunDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(BatchRunDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        trSetBox = new QComboBox(BatchRunDialog);
        trSetBox->setObjectName(QString::fromUtf8("trSetBox"));

        horizontalLayout->addWidget(trSetBox);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(17, 373, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(533, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(BatchRunDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(BatchRunDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), BatchRunDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BatchRunDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BatchRunDialog);
    } // setupUi

    void retranslateUi(QDialog *BatchRunDialog)
    {
        BatchRunDialog->setWindowTitle(QApplication::translate("BatchRunDialog", "Traceroute Initiation", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BatchRunDialog", "Traceroute Set", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BatchRunDialog: public Ui_BatchRunDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATCHRUN_H

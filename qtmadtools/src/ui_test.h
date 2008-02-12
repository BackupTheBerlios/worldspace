/********************************************************************************
** Form generated from reading ui file 'test.ui'
**
** Created: Sun Feb 10 10:25:36 2008
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QWidget>

class Ui_Form {
  public:
    QCalendarWidget * calendarWidget;

    void setupUi(QWidget * Form) {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        calendarWidget = new QCalendarWidget(Form);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(70, 50, 272, 166));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi void retranslateUi(QWidget * Form) {
        Form->
            setWindowTitle(QApplication::
                           translate("Form", "Form", 0,
                                     QApplication::UnicodeUTF8));
        Q_UNUSED(Form);
    }                           // retranslateUi

};

namespace Ui {
    class Form:public Ui_Form {
    };
}                               // namespace Ui
#endif                          // UI_TEST_H

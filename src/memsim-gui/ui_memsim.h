/********************************************************************************
** Form generated from reading UI file 'memsim.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMSIM_H
#define UI_MEMSIM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <memsimvis.h>
#include <powerspinbox.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRun;
    QAction *action_Load_File;
    QAction *action_Settings;
    QAction *actionRun_stp;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *step_button;
    QToolButton *finish_button;
    QSpacerItem *horizontalSpacer;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QTabWidget *viztabs;
    QWidget *l1tab;
    QGridLayout *gridLayout_3;
    MemSimVis *widget;
    QWidget *l2tab;
    QWidget *l3tab;
    QFrame *frame_3;
    QFormLayout *formLayout_2;
    QLabel *labsd;
    QLineEdit *l1acc;
    QLabel *l;
    QLineEdit *l1missval;
    QLabel *label_17;
    QLineEdit *l2acc;
    QLabel *label_18;
    QLineEdit *l2missval;
    QLabel *label_19;
    QLineEdit *l3acc;
    QLabel *label_20;
    QLineEdit *l3missval;
    QLabel *label_21;
    QLineEdit *tlbacc;
    QLabel *label_22;
    QLineEdit *tlbmissval;
    QLabel *label_23;
    QLineEdit *time;
    QLabel *label_24;
    QLineEdit *accesses;
    QFormLayout *formLayout;
    QCheckBox *l1check;
    QRadioButton *anoldradio;
    QRadioButton *neldradio;
    QLabel *label_2;
    QSpinBox *l1miss;
    QLabel *label_6;
    PowerSpinBox *l1size;
    QLabel *label_7;
    PowerSpinBox *l1assoc;
    QCheckBox *l2check;
    QLabel *label_5;
    QSpinBox *l2miss;
    QLabel *label_3;
    PowerSpinBox *l2size;
    QLabel *label_4;
    PowerSpinBox *l2assoc;
    QCheckBox *l3check;
    QLabel *label_12;
    QSpinBox *l3miss;
    QLabel *label_8;
    PowerSpinBox *l3size;
    QLabel *label_9;
    PowerSpinBox *l3assoc;
    QCheckBox *tlbcheck;
    QLabel *label;
    QSpinBox *tlbmiss;
    QLabel *label_10;
    PowerSpinBox *tlbentries;
    QLabel *label_11;
    PowerSpinBox *tlbassoc;
    QCheckBox *pgtblcheck;
    QLabel *label_13;
    QSpinBox *pgtablemiss;
    QLabel *label_14;
    QPushButton *pushButton;
    QSpinBox *swapmiss;
    QCheckBox *swapcheck;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuSimulation;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1178, 1025);
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QString::fromUtf8("actionRun"));
        action_Load_File = new QAction(MainWindow);
        action_Load_File->setObjectName(QString::fromUtf8("action_Load_File"));
        action_Settings = new QAction(MainWindow);
        action_Settings->setObjectName(QString::fromUtf8("action_Settings"));
        actionRun_stp = new QAction(MainWindow);
        actionRun_stp->setObjectName(QString::fromUtf8("actionRun_stp"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 8);
        step_button = new QToolButton(centralwidget);
        step_button->setObjectName(QString::fromUtf8("step_button"));
        step_button->setEnabled(true);

        horizontalLayout_3->addWidget(step_button);

        finish_button = new QToolButton(centralwidget);
        finish_button->setObjectName(QString::fromUtf8("finish_button"));
        finish_button->setEnabled(true);

        horizontalLayout_3->addWidget(finish_button);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(frame_2);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

        horizontalLayout->addWidget(tabWidget);

        frame = new QFrame(frame_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        viztabs = new QTabWidget(frame);
        viztabs->setObjectName(QString::fromUtf8("viztabs"));
        l1tab = new QWidget();
        l1tab->setObjectName(QString::fromUtf8("l1tab"));
        gridLayout_3 = new QGridLayout(l1tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget = new MemSimVis(l1tab);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        viztabs->addTab(l1tab, QString());
        l2tab = new QWidget();
        l2tab->setObjectName(QString::fromUtf8("l2tab"));
        viztabs->addTab(l2tab, QString());
        l3tab = new QWidget();
        l3tab->setObjectName(QString::fromUtf8("l3tab"));
        viztabs->addTab(l3tab, QString());

        gridLayout_2->addWidget(viztabs, 0, 0, 1, 1);


        horizontalLayout->addWidget(frame);

        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy1);
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        formLayout_2 = new QFormLayout(frame_3);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labsd = new QLabel(frame_3);
        labsd->setObjectName(QString::fromUtf8("labsd"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, labsd);

        l1acc = new QLineEdit(frame_3);
        l1acc->setObjectName(QString::fromUtf8("l1acc"));
        l1acc->setEnabled(false);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, l1acc);

        l = new QLabel(frame_3);
        l->setObjectName(QString::fromUtf8("l"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, l);

        l1missval = new QLineEdit(frame_3);
        l1missval->setObjectName(QString::fromUtf8("l1missval"));
        l1missval->setEnabled(false);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, l1missval);

        label_17 = new QLabel(frame_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_17);

        l2acc = new QLineEdit(frame_3);
        l2acc->setObjectName(QString::fromUtf8("l2acc"));
        l2acc->setEnabled(false);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, l2acc);

        label_18 = new QLabel(frame_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_18);

        l2missval = new QLineEdit(frame_3);
        l2missval->setObjectName(QString::fromUtf8("l2missval"));
        l2missval->setEnabled(false);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, l2missval);

        label_19 = new QLabel(frame_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_19);

        l3acc = new QLineEdit(frame_3);
        l3acc->setObjectName(QString::fromUtf8("l3acc"));
        l3acc->setEnabled(false);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, l3acc);

        label_20 = new QLabel(frame_3);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_20);

        l3missval = new QLineEdit(frame_3);
        l3missval->setObjectName(QString::fromUtf8("l3missval"));
        l3missval->setEnabled(false);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, l3missval);

        label_21 = new QLabel(frame_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_21);

        tlbacc = new QLineEdit(frame_3);
        tlbacc->setObjectName(QString::fromUtf8("tlbacc"));
        tlbacc->setEnabled(false);

        formLayout_2->setWidget(6, QFormLayout::FieldRole, tlbacc);

        label_22 = new QLabel(frame_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, label_22);

        tlbmissval = new QLineEdit(frame_3);
        tlbmissval->setObjectName(QString::fromUtf8("tlbmissval"));
        tlbmissval->setEnabled(false);

        formLayout_2->setWidget(7, QFormLayout::FieldRole, tlbmissval);

        label_23 = new QLabel(frame_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        formLayout_2->setWidget(9, QFormLayout::LabelRole, label_23);

        time = new QLineEdit(frame_3);
        time->setObjectName(QString::fromUtf8("time"));
        time->setEnabled(false);

        formLayout_2->setWidget(9, QFormLayout::FieldRole, time);

        label_24 = new QLabel(frame_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        formLayout_2->setWidget(10, QFormLayout::LabelRole, label_24);

        accesses = new QLineEdit(frame_3);
        accesses->setObjectName(QString::fromUtf8("accesses"));
        accesses->setEnabled(false);

        formLayout_2->setWidget(10, QFormLayout::FieldRole, accesses);


        horizontalLayout->addWidget(frame_3);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        l1check = new QCheckBox(frame_2);
        l1check->setObjectName(QString::fromUtf8("l1check"));

        formLayout->setWidget(0, QFormLayout::LabelRole, l1check);

        anoldradio = new QRadioButton(frame_2);
        anoldradio->setObjectName(QString::fromUtf8("anoldradio"));

        formLayout->setWidget(1, QFormLayout::LabelRole, anoldradio);

        neldradio = new QRadioButton(frame_2);
        neldradio->setObjectName(QString::fromUtf8("neldradio"));

        formLayout->setWidget(2, QFormLayout::LabelRole, neldradio);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        l1miss = new QSpinBox(frame_2);
        l1miss->setObjectName(QString::fromUtf8("l1miss"));
        l1miss->setMinimum(1);
        l1miss->setMaximum(999999999);

        formLayout->setWidget(3, QFormLayout::FieldRole, l1miss);

        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_6);

        l1size = new PowerSpinBox(frame_2);
        l1size->setObjectName(QString::fromUtf8("l1size"));
        l1size->setMinimum(2);
        l1size->setMaximum(999999999);

        formLayout->setWidget(4, QFormLayout::FieldRole, l1size);

        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_7);

        l1assoc = new PowerSpinBox(frame_2);
        l1assoc->setObjectName(QString::fromUtf8("l1assoc"));
        l1assoc->setMinimum(1);
        l1assoc->setMaximum(999999999);

        formLayout->setWidget(5, QFormLayout::FieldRole, l1assoc);

        l2check = new QCheckBox(frame_2);
        l2check->setObjectName(QString::fromUtf8("l2check"));

        formLayout->setWidget(6, QFormLayout::LabelRole, l2check);

        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_5);

        l2miss = new QSpinBox(frame_2);
        l2miss->setObjectName(QString::fromUtf8("l2miss"));
        l2miss->setMinimum(1);
        l2miss->setMaximum(999999999);

        formLayout->setWidget(7, QFormLayout::FieldRole, l2miss);

        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_3);

        l2size = new PowerSpinBox(frame_2);
        l2size->setObjectName(QString::fromUtf8("l2size"));
        l2size->setMinimum(2);
        l2size->setMaximum(999999999);

        formLayout->setWidget(8, QFormLayout::FieldRole, l2size);

        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_4);

        l2assoc = new PowerSpinBox(frame_2);
        l2assoc->setObjectName(QString::fromUtf8("l2assoc"));
        l2assoc->setMinimum(1);
        l2assoc->setMaximum(999999999);

        formLayout->setWidget(9, QFormLayout::FieldRole, l2assoc);

        l3check = new QCheckBox(frame_2);
        l3check->setObjectName(QString::fromUtf8("l3check"));

        formLayout->setWidget(10, QFormLayout::LabelRole, l3check);

        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout->setWidget(11, QFormLayout::LabelRole, label_12);

        l3miss = new QSpinBox(frame_2);
        l3miss->setObjectName(QString::fromUtf8("l3miss"));
        l3miss->setMinimum(1);
        l3miss->setMaximum(999999999);

        formLayout->setWidget(11, QFormLayout::FieldRole, l3miss);

        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label_8);

        l3size = new PowerSpinBox(frame_2);
        l3size->setObjectName(QString::fromUtf8("l3size"));
        l3size->setMinimum(2);
        l3size->setMaximum(999999999);

        formLayout->setWidget(12, QFormLayout::FieldRole, l3size);

        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(13, QFormLayout::LabelRole, label_9);

        l3assoc = new PowerSpinBox(frame_2);
        l3assoc->setObjectName(QString::fromUtf8("l3assoc"));
        l3assoc->setMinimum(1);
        l3assoc->setMaximum(999999999);

        formLayout->setWidget(13, QFormLayout::FieldRole, l3assoc);

        tlbcheck = new QCheckBox(frame_2);
        tlbcheck->setObjectName(QString::fromUtf8("tlbcheck"));

        formLayout->setWidget(14, QFormLayout::LabelRole, tlbcheck);

        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(15, QFormLayout::LabelRole, label);

        tlbmiss = new QSpinBox(frame_2);
        tlbmiss->setObjectName(QString::fromUtf8("tlbmiss"));
        tlbmiss->setMinimum(1);
        tlbmiss->setMaximum(999999999);

        formLayout->setWidget(15, QFormLayout::FieldRole, tlbmiss);

        label_10 = new QLabel(frame_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(16, QFormLayout::LabelRole, label_10);

        tlbentries = new PowerSpinBox(frame_2);
        tlbentries->setObjectName(QString::fromUtf8("tlbentries"));
        tlbentries->setMinimum(1);
        tlbentries->setMaximum(999999999);

        formLayout->setWidget(16, QFormLayout::FieldRole, tlbentries);

        label_11 = new QLabel(frame_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(17, QFormLayout::LabelRole, label_11);

        tlbassoc = new PowerSpinBox(frame_2);
        tlbassoc->setObjectName(QString::fromUtf8("tlbassoc"));
        tlbassoc->setMinimum(1);
        tlbassoc->setMaximum(999999999);

        formLayout->setWidget(17, QFormLayout::FieldRole, tlbassoc);

        pgtblcheck = new QCheckBox(frame_2);
        pgtblcheck->setObjectName(QString::fromUtf8("pgtblcheck"));

        formLayout->setWidget(18, QFormLayout::LabelRole, pgtblcheck);

        label_13 = new QLabel(frame_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout->setWidget(19, QFormLayout::LabelRole, label_13);

        pgtablemiss = new QSpinBox(frame_2);
        pgtablemiss->setObjectName(QString::fromUtf8("pgtablemiss"));
        pgtablemiss->setMinimum(1);
        pgtablemiss->setMaximum(999999999);

        formLayout->setWidget(19, QFormLayout::FieldRole, pgtablemiss);

        label_14 = new QLabel(frame_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        formLayout->setWidget(21, QFormLayout::LabelRole, label_14);

        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        formLayout->setWidget(22, QFormLayout::LabelRole, pushButton);

        swapmiss = new QSpinBox(frame_2);
        swapmiss->setObjectName(QString::fromUtf8("swapmiss"));
        swapmiss->setMinimum(1);
        swapmiss->setMaximum(999999999);

        formLayout->setWidget(21, QFormLayout::FieldRole, swapmiss);

        swapcheck = new QCheckBox(frame_2);
        swapcheck->setObjectName(QString::fromUtf8("swapcheck"));

        formLayout->setWidget(20, QFormLayout::LabelRole, swapcheck);


        horizontalLayout->addLayout(formLayout);


        verticalLayout->addWidget(frame_2);

        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setEnabled(true);
        plainTextEdit->setReadOnly(true);

        verticalLayout->addWidget(plainTextEdit);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1178, 27));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuSimulation = new QMenu(menubar);
        menuSimulation->setObjectName(QString::fromUtf8("menuSimulation"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuSimulation->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(action_Load_File);
        menuEdit->addAction(action_Settings);
        menuSimulation->addAction(actionRun);
        menuSimulation->addAction(actionRun_stp);

        retranslateUi(MainWindow);
        QObject::connect(pgtblcheck, SIGNAL(clicked(bool)), tlbcheck, SLOT(setEnabled(bool)));
        QObject::connect(pgtblcheck, SIGNAL(clicked(bool)), swapcheck, SLOT(setEnabled(bool)));

        viztabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MemSim", 0, QApplication::UnicodeUTF8));
        actionRun->setText(QApplication::translate("MainWindow", "R&un", 0, QApplication::UnicodeUTF8));
        action_Load_File->setText(QApplication::translate("MainWindow", "&Load File", 0, QApplication::UnicodeUTF8));
        action_Settings->setText(QApplication::translate("MainWindow", "&Settings", 0, QApplication::UnicodeUTF8));
        actionRun_stp->setText(QApplication::translate("MainWindow", "Run step", 0, QApplication::UnicodeUTF8));
        step_button->setText(QApplication::translate("MainWindow", "Step", 0, QApplication::UnicodeUTF8));
        finish_button->setText(QApplication::translate("MainWindow", "Finish", 0, QApplication::UnicodeUTF8));
        viztabs->setTabText(viztabs->indexOf(l1tab), QApplication::translate("MainWindow", "L1", 0, QApplication::UnicodeUTF8));
        viztabs->setTabText(viztabs->indexOf(l2tab), QApplication::translate("MainWindow", "L2", 0, QApplication::UnicodeUTF8));
        viztabs->setTabText(viztabs->indexOf(l3tab), QApplication::translate("MainWindow", "L3", 0, QApplication::UnicodeUTF8));
        labsd->setText(QApplication::translate("MainWindow", "L1 acc", 0, QApplication::UnicodeUTF8));
        l->setText(QApplication::translate("MainWindow", "L1 miss", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "L2 acc", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "L2 miss", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "L3 acc", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "L3 miss", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("MainWindow", "TLB acc", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("MainWindow", "TLB miss", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("MainWindow", "Time", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("MainWindow", "Accesses", 0, QApplication::UnicodeUTF8));
        l1check->setText(QApplication::translate("MainWindow", "L1", 0, QApplication::UnicodeUTF8));
        anoldradio->setText(QApplication::translate("MainWindow", "I a D spole\304\215n\303\251", 0, QApplication::UnicodeUTF8));
        neldradio->setText(QApplication::translate("MainWindow", "I a D odd\304\233leny", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "MissTime", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Velikost", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Asociativita", 0, QApplication::UnicodeUTF8));
        l2check->setText(QApplication::translate("MainWindow", "L2", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "MissTime", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Velikost", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Asociativita", 0, QApplication::UnicodeUTF8));
        l3check->setText(QApplication::translate("MainWindow", "L3", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "MissTime", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Velikost", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Asociativita", 0, QApplication::UnicodeUTF8));
        tlbcheck->setText(QApplication::translate("MainWindow", "TLB", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "MissTime", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Polo\305\276ky", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Asociativita", 0, QApplication::UnicodeUTF8));
        pgtblcheck->setText(QApplication::translate("MainWindow", "Tabulka str\303\241nek", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "AvgMissTime", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "LoadTime", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Ulo\305\276it", 0, QApplication::UnicodeUTF8));
        swapcheck->setText(QApplication::translate("MainWindow", "Swap", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
        menuSimulation->setTitle(QApplication::translate("MainWindow", "&Simulation", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMSIM_H

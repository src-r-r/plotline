/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_Novel;
    QAction *actionNovel;
    QAction *actionCharacter;
    QAction *actionNewScene;
    QAction *actionPart;
    QAction *actionChapter;
    QAction *actionExport;
    QAction *actionCreate_Book;
    QAction *actionQuit;
    QAction *actionNovel_2;
    QAction *actionScene;
    QAction *actionCharacters;
    QAction *actionScenes;
    QAction *actionChapters;
    QAction *actionDonate;
    QAction *actionPreferences;
    QAction *actionAbout;
    QAction *actionHelp;
    QAction *actionClose_Novel;
    QAction *actionSAve;
    QAction *actionPlotline;
    QAction *actionFocus_Mode;
    QAction *actionEdit_Mode;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tabNovel;
    QSplitter *splitter;
    QListWidget *novelPartsList;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *tab_characters;
    QSplitter *splitter_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QTreeView *characterList;
    QHBoxLayout *horizontalLayout;
    QPushButton *addCharacter;
    QPushButton *archiveCharacter;
    QPushButton *deleteCharacter;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *tab_plotlines;
    QGridLayout *gridLayout_2;
    QSplitter *splitter_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QListView *listView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_4;
    QGridLayout *gridLayout_3;
    QFormLayout *formLayout;
    QLabel *plotDescriptionLabel;
    QLineEdit *plotlineDescription;
    QLabel *plotDetailsLabel;
    QTextEdit *plotlineDetails;
    QLabel *plotlinePovLabel;
    QLineEdit *plotlinePov;
    QWidget *tab_scenes;
    QWidget *tab_chapters;
    QWidget *tab_donate;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuNew;
    QMenu *menuGo_To;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuMode;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(745, 518);
        actionOpen_Novel = new QAction(MainWindow);
        actionOpen_Novel->setObjectName(QStringLiteral("actionOpen_Novel"));
        actionNovel = new QAction(MainWindow);
        actionNovel->setObjectName(QStringLiteral("actionNovel"));
        actionCharacter = new QAction(MainWindow);
        actionCharacter->setObjectName(QStringLiteral("actionCharacter"));
        actionNewScene = new QAction(MainWindow);
        actionNewScene->setObjectName(QStringLiteral("actionNewScene"));
        actionPart = new QAction(MainWindow);
        actionPart->setObjectName(QStringLiteral("actionPart"));
        actionChapter = new QAction(MainWindow);
        actionChapter->setObjectName(QStringLiteral("actionChapter"));
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        actionCreate_Book = new QAction(MainWindow);
        actionCreate_Book->setObjectName(QStringLiteral("actionCreate_Book"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionNovel_2 = new QAction(MainWindow);
        actionNovel_2->setObjectName(QStringLiteral("actionNovel_2"));
        actionScene = new QAction(MainWindow);
        actionScene->setObjectName(QStringLiteral("actionScene"));
        actionCharacters = new QAction(MainWindow);
        actionCharacters->setObjectName(QStringLiteral("actionCharacters"));
        actionScenes = new QAction(MainWindow);
        actionScenes->setObjectName(QStringLiteral("actionScenes"));
        actionChapters = new QAction(MainWindow);
        actionChapters->setObjectName(QStringLiteral("actionChapters"));
        actionDonate = new QAction(MainWindow);
        actionDonate->setObjectName(QStringLiteral("actionDonate"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        actionDonate->setFont(font);
        actionPreferences = new QAction(MainWindow);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionClose_Novel = new QAction(MainWindow);
        actionClose_Novel->setObjectName(QStringLiteral("actionClose_Novel"));
        actionSAve = new QAction(MainWindow);
        actionSAve->setObjectName(QStringLiteral("actionSAve"));
        actionPlotline = new QAction(MainWindow);
        actionPlotline->setObjectName(QStringLiteral("actionPlotline"));
        actionFocus_Mode = new QAction(MainWindow);
        actionFocus_Mode->setObjectName(QStringLiteral("actionFocus_Mode"));
        actionEdit_Mode = new QAction(MainWindow);
        actionEdit_Mode->setObjectName(QStringLiteral("actionEdit_Mode"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabNovel = new QWidget();
        tabNovel->setObjectName(QStringLiteral("tabNovel"));
        splitter = new QSplitter(tabNovel);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(0, 0, 721, 411));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        novelPartsList = new QListWidget(splitter);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(novelPartsList);
        __qlistwidgetitem->setFont(font);
        new QListWidgetItem(novelPartsList);
        new QListWidgetItem(novelPartsList);
        new QListWidgetItem(novelPartsList);
        novelPartsList->setObjectName(QStringLiteral("novelPartsList"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(novelPartsList->sizePolicy().hasHeightForWidth());
        novelPartsList->setSizePolicy(sizePolicy1);
        novelPartsList->setMaximumSize(QSize(90, 16777215));
        splitter->addWidget(novelPartsList);
        scrollArea = new QScrollArea(splitter);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy2);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 623, 409));
        scrollArea->setWidget(scrollAreaWidgetContents_2);
        splitter->addWidget(scrollArea);
        tabWidget->addTab(tabNovel, QString());
        tab_characters = new QWidget();
        tab_characters->setObjectName(QStringLiteral("tab_characters"));
        sizePolicy.setHeightForWidth(tab_characters->sizePolicy().hasHeightForWidth());
        tab_characters->setSizePolicy(sizePolicy);
        splitter_2 = new QSplitter(tab_characters);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(0, 0, 711, 401));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy3);
        splitter_2->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        characterList = new QTreeView(layoutWidget);
        characterList->setObjectName(QStringLiteral("characterList"));
        sizePolicy1.setHeightForWidth(characterList->sizePolicy().hasHeightForWidth());
        characterList->setSizePolicy(sizePolicy1);
        characterList->setMinimumSize(QSize(200, 0));
        characterList->setMaximumSize(QSize(200, 16777215));

        verticalLayout_2->addWidget(characterList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        addCharacter = new QPushButton(layoutWidget);
        addCharacter->setObjectName(QStringLiteral("addCharacter"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(addCharacter->sizePolicy().hasHeightForWidth());
        addCharacter->setSizePolicy(sizePolicy4);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/resources/images/list-add-user.png"), QSize(), QIcon::Normal, QIcon::Off);
        addCharacter->setIcon(icon);
        addCharacter->setFlat(false);

        horizontalLayout->addWidget(addCharacter);

        archiveCharacter = new QPushButton(layoutWidget);
        archiveCharacter->setObjectName(QStringLiteral("archiveCharacter"));
        sizePolicy4.setHeightForWidth(archiveCharacter->sizePolicy().hasHeightForWidth());
        archiveCharacter->setSizePolicy(sizePolicy4);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/resources/images/user-archive.png"), QSize(), QIcon::Normal, QIcon::Off);
        archiveCharacter->setIcon(icon1);

        horizontalLayout->addWidget(archiveCharacter);

        deleteCharacter = new QPushButton(layoutWidget);
        deleteCharacter->setObjectName(QStringLiteral("deleteCharacter"));
        sizePolicy4.setHeightForWidth(deleteCharacter->sizePolicy().hasHeightForWidth());
        deleteCharacter->setSizePolicy(sizePolicy4);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/resources/images/list-remove-user.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteCharacter->setIcon(icon2);

        horizontalLayout->addWidget(deleteCharacter);


        verticalLayout_2->addLayout(horizontalLayout);

        splitter_2->addWidget(layoutWidget);
        scrollArea_2 = new QScrollArea(splitter_2);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        sizePolicy1.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy1);
        scrollArea_2->setMinimumSize(QSize(500, 0));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 498, 399));
        scrollArea_2->setWidget(scrollAreaWidgetContents_3);
        splitter_2->addWidget(scrollArea_2);
        tabWidget->addTab(tab_characters, QString());
        tab_plotlines = new QWidget();
        tab_plotlines->setObjectName(QStringLiteral("tab_plotlines"));
        gridLayout_2 = new QGridLayout(tab_plotlines);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter_3 = new QSplitter(tab_plotlines);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        layoutWidget1 = new QWidget(splitter_3);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listView = new QListView(layoutWidget1);
        listView->setObjectName(QStringLiteral("listView"));
        sizePolicy1.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy1);
        listView->setMinimumSize(QSize(0, 0));
        listView->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(listView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(layoutWidget1);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(pushButton);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy4.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy4);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/resources/images/list-add-plotline.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon3);

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget1);
        buttonGroup->addButton(pushButton_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy4.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy4);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix1/resources/images/list-remove-plotline.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon4);

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_2);

        splitter_3->addWidget(layoutWidget1);
        scrollArea_3 = new QScrollArea(splitter_3);
        scrollArea_3->setObjectName(QStringLiteral("scrollArea_3"));
        sizePolicy2.setHeightForWidth(scrollArea_3->sizePolicy().hasHeightForWidth());
        scrollArea_3->setSizePolicy(sizePolicy2);
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QStringLiteral("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 361, 387));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        plotDescriptionLabel = new QLabel(scrollAreaWidgetContents_4);
        plotDescriptionLabel->setObjectName(QStringLiteral("plotDescriptionLabel"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, plotDescriptionLabel);

        plotlineDescription = new QLineEdit(scrollAreaWidgetContents_4);
        plotlineDescription->setObjectName(QStringLiteral("plotlineDescription"));

        formLayout->setWidget(1, QFormLayout::SpanningRole, plotlineDescription);

        plotDetailsLabel = new QLabel(scrollAreaWidgetContents_4);
        plotDetailsLabel->setObjectName(QStringLiteral("plotDetailsLabel"));

        formLayout->setWidget(2, QFormLayout::SpanningRole, plotDetailsLabel);

        plotlineDetails = new QTextEdit(scrollAreaWidgetContents_4);
        plotlineDetails->setObjectName(QStringLiteral("plotlineDetails"));

        formLayout->setWidget(3, QFormLayout::SpanningRole, plotlineDetails);

        plotlinePovLabel = new QLabel(scrollAreaWidgetContents_4);
        plotlinePovLabel->setObjectName(QStringLiteral("plotlinePovLabel"));

        formLayout->setWidget(4, QFormLayout::SpanningRole, plotlinePovLabel);

        plotlinePov = new QLineEdit(scrollAreaWidgetContents_4);
        plotlinePov->setObjectName(QStringLiteral("plotlinePov"));

        formLayout->setWidget(5, QFormLayout::SpanningRole, plotlinePov);


        gridLayout_3->addLayout(formLayout, 0, 0, 1, 1);

        scrollArea_3->setWidget(scrollAreaWidgetContents_4);
        splitter_3->addWidget(scrollArea_3);

        gridLayout_2->addWidget(splitter_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_plotlines, QString());
        tab_scenes = new QWidget();
        tab_scenes->setObjectName(QStringLiteral("tab_scenes"));
        tabWidget->addTab(tab_scenes, QString());
        tab_chapters = new QWidget();
        tab_chapters->setObjectName(QStringLiteral("tab_chapters"));
        tabWidget->addTab(tab_chapters, QString());
        tab_donate = new QWidget();
        tab_donate->setObjectName(QStringLiteral("tab_donate"));
        tabWidget->addTab(tab_donate, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 745, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuNew = new QMenu(menuFile);
        menuNew->setObjectName(QStringLiteral("menuNew"));
        menuGo_To = new QMenu(menuBar);
        menuGo_To->setObjectName(QStringLiteral("menuGo_To"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuMode = new QMenu(menuView);
        menuMode->setObjectName(QStringLiteral("menuMode"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuGo_To->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(menuNew->menuAction());
        menuFile->addAction(actionOpen_Novel);
        menuFile->addAction(actionSAve);
        menuFile->addSeparator();
        menuFile->addAction(actionExport);
        menuFile->addAction(actionCreate_Book);
        menuFile->addSeparator();
        menuFile->addAction(actionClose_Novel);
        menuFile->addAction(actionQuit);
        menuNew->addAction(actionCharacter);
        menuNew->addAction(actionNovel_2);
        menuNew->addSeparator();
        menuNew->addAction(actionPlotline);
        menuNew->addAction(actionNewScene);
        menuNew->addSeparator();
        menuNew->addAction(actionPart);
        menuNew->addAction(actionChapter);
        menuGo_To->addAction(actionScene);
        menuGo_To->addAction(actionCharacters);
        menuGo_To->addAction(actionScenes);
        menuGo_To->addAction(actionChapters);
        menuGo_To->addAction(actionDonate);
        menuEdit->addAction(actionPreferences);
        menuEdit->addAction(actionAbout);
        menuEdit->addAction(actionHelp);
        menuView->addAction(menuMode->menuAction());
        menuMode->addAction(actionFocus_Mode);
        menuMode->addAction(actionEdit_Mode);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen_Novel->setText(QApplication::translate("MainWindow", "&Open", 0));
        actionNovel->setText(QApplication::translate("MainWindow", "Novel", 0));
        actionCharacter->setText(QApplication::translate("MainWindow", "&Character", 0));
        actionNewScene->setText(QApplication::translate("MainWindow", "&Scene", 0));
#ifndef QT_NO_TOOLTIP
        actionNewScene->setToolTip(QApplication::translate("MainWindow", "New Scene", 0));
#endif // QT_NO_TOOLTIP
        actionPart->setText(QApplication::translate("MainWindow", "Pa&rt", 0));
        actionChapter->setText(QApplication::translate("MainWindow", "C&hapter", 0));
        actionExport->setText(QApplication::translate("MainWindow", "&Export", 0));
        actionCreate_Book->setText(QApplication::translate("MainWindow", "&Bind Novel", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0));
        actionNovel_2->setText(QApplication::translate("MainWindow", "&Novel", 0));
        actionScene->setText(QApplication::translate("MainWindow", "&Novel", 0));
        actionCharacters->setText(QApplication::translate("MainWindow", "&Characters", 0));
        actionScenes->setText(QApplication::translate("MainWindow", "&Scenes", 0));
        actionChapters->setText(QApplication::translate("MainWindow", "C&hapters", 0));
        actionDonate->setText(QApplication::translate("MainWindow", "&Donate", 0));
        actionPreferences->setText(QApplication::translate("MainWindow", "&Preferences", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "&About", 0));
        actionHelp->setText(QApplication::translate("MainWindow", "&Help", 0));
        actionClose_Novel->setText(QApplication::translate("MainWindow", "&Close Novel", 0));
        actionSAve->setText(QApplication::translate("MainWindow", "&Save", 0));
        actionPlotline->setText(QApplication::translate("MainWindow", "&Plotline", 0));
        actionFocus_Mode->setText(QApplication::translate("MainWindow", "&Focus Mode", 0));
        actionEdit_Mode->setText(QApplication::translate("MainWindow", "&Edit Mode", 0));

        const bool __sortingEnabled = novelPartsList->isSortingEnabled();
        novelPartsList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = novelPartsList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "Overview", 0));
        QListWidgetItem *___qlistwidgetitem1 = novelPartsList->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "Part 1", 0));
        QListWidgetItem *___qlistwidgetitem2 = novelPartsList->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("MainWindow", "Part 2", 0));
        QListWidgetItem *___qlistwidgetitem3 = novelPartsList->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("MainWindow", "Part 3", 0));
        novelPartsList->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tabNovel), QApplication::translate("MainWindow", "Novel", 0));
        addCharacter->setText(QString());
        archiveCharacter->setText(QString());
        deleteCharacter->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_characters), QApplication::translate("MainWindow", "Characters", 0));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        plotDescriptionLabel->setText(QApplication::translate("MainWindow", "Description:", 0));
        plotDetailsLabel->setText(QApplication::translate("MainWindow", "Details:", 0));
        plotlinePovLabel->setText(QApplication::translate("MainWindow", "Point Of View:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_plotlines), QApplication::translate("MainWindow", "Plot Lines", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_scenes), QApplication::translate("MainWindow", "Scenes", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_chapters), QApplication::translate("MainWindow", "Chapters", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_donate), QApplication::translate("MainWindow", "Donate", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "Fi&le", 0));
        menuNew->setTitle(QApplication::translate("MainWindow", "&New", 0));
        menuGo_To->setTitle(QApplication::translate("MainWindow", "&Go  To...", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Applicatio&n", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "&View", 0));
        menuMode->setTitle(QApplication::translate("MainWindow", "&Mode", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#include <QtWidgets>

#include "startWindow/CommonDefinitions.hpp"
#include "startWindow/GetStartedWindow.hpp"
#include "startWindow/GetStartedMenuButton.hpp"

namespace {
	const QString iconfolder("f:/projects/MofIP/client/gui/mofipwidgets/icons");
	constexpr int spaceFromTopWidget = 50;
	constexpr int spaceBetweenVLayouts = 50;
}

namespace mofipgui {

	GetStartedWindow::GetStartedWindow(QWidget* wgt)
		: FramelessWindow(wgt)
	{
		setMinimumSize(720, 480);

		QString labeltext(tr("MofIP Application 2023"));

		// Set app name
		// ----------------------------------------------
		QFont namefont(QApplication::font());
		namefont.setPointSize(22);
		namefont.setBold(true);

		m_plblAppName = new QLabel(labeltext, this);
		m_plblAppName->setFont(namefont);
		m_plblAppName->setMinimumWidth(QFontMetrics(namefont).width(labeltext));
		m_plblAppName->move(20, 20);


		// Left get started layout
		// ----------------------------------------------
		QLabel* getStartedLabel = new QLabel("  Get Started");
		namefont.setPointSize(14);
		getStartedLabel->setFont(namefont);

		m_pbtnCreateProject = new GetStartedMenuButton(iconfolder + "/newproject.png");
		m_pbtnCreateProject->setMainText("Create Project");
		m_pbtnCreateProject->setHintText("Create new solution/project \nwith concrete type");
		m_pbtnOpenProject = new GetStartedMenuButton(iconfolder + "/openproject.png");
		m_pbtnOpenProject->setMainText("Open Project");
		m_pbtnOpenProject->setHintText("Open project from \nlocal machine(from disk)");
		m_pbtnCloneProject = new GetStartedMenuButton(iconfolder + "/loadproject.png");
		m_pbtnCloneProject->setMainText("Clone Project");
		m_pbtnCloneProject->setHintText("Create project/solution \nwith project from server");

		QVBoxLayout* getStartedLayout = new QVBoxLayout;
		getStartedLayout->addSpacing(TOOL_BUTTON_RECT.height() + spaceFromTopWidget);
		getStartedLayout->addWidget(getStartedLabel);
		getStartedLayout->addSpacing(5);
		getStartedLayout->addWidget(m_pbtnCreateProject);
		getStartedLayout->addWidget(m_pbtnOpenProject);
		getStartedLayout->addWidget(m_pbtnCloneProject);
		getStartedLayout->addStretch();

		// Right show project vertical layout
		// ----------------------------------------------
		QLabel* showExistingProjectsLbl = new QLabel("Later Projects ...");
		showExistingProjectsLbl->setFont(namefont);
		
		QVBoxLayout* showProjectLayout = new QVBoxLayout;
		showProjectLayout->addSpacing(TOOL_BUTTON_RECT.height() + spaceFromTopWidget);
		showProjectLayout->addWidget(showExistingProjectsLbl);
		showProjectLayout->addStretch();

		// Central/main get started widget Layout
		// ----------------------------------------------
		QHBoxLayout* phbxLayout = new QHBoxLayout;
		phbxLayout->addSpacing(TOOL_BUTTON_RECT.width());
		phbxLayout->addLayout(getStartedLayout);
		phbxLayout->addSpacing(spaceBetweenVLayouts);
		phbxLayout->addLayout(showProjectLayout);
		phbxLayout->addStretch();
		setLayout(phbxLayout);
	}

}

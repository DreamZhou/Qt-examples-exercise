							第五章
一 主窗口框架
	QMainWindow 
		包含 菜单栏(QMenuBar), 工具栏(QToolBar), 中心部件(Central Widget) 
		Dock部件(QDockWidget), 状态栏(QStatusBar)
	1.使用资源  
	2. 代码方式添加菜单 
	    添加 头文件 --> QMenu --> QAction --> setShortCut --> ui->maitToolBar->addAction
	3. 菜单栏
		间隔器(addSeparator())  
		QAction 包括 图标, 菜单显示文本, 快捷键, 
					状态栏显示文本,"What's This"显示文本及工具提示文本
					checkable 属性: 选中这个菜单  表示选中
	4. QActionGroup 可以包含一组动作 QAction 
	5. 工具栏QToolBar 
	    toolButtonStyle 设置图标和相应文本的显示及其相对位置
		movable 设置状态栏是否可以移动
		allowedArea 设置允许停靠的位置
		iconsize 设置图标的大小
		floatable 设置是否可以悬浮
	6. 中心部件
	    QTextEdit  QMidArea  QMidSubWindow
	7. Dock部件
	8.  状态栏显示文本 
	     a, 临时信息   showMessage()
		 b, 正常信息   addWidget() 添加一个Qlabel 到状态栏，他会生成到状态栏的最左边，可能被临时消息覆盖
		 c, 永久信息   addPermanentWidget() 添加一个Qlabel到最右边。不会被临时消息覆盖
		QsizeGrip部件 来调整窗口大小。 setSizeGripEnabled() 禁用。
		

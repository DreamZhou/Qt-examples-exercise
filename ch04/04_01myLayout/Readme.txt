a, 单击主界面 按下 Ctrl +L 快捷键 ，设置顶层布局管理器，
b, 与 选中 Font Combo Box 和 Text Edit 部件 设置 垂直布局不一样！！
 
水平布局 Ctrl+H
垂直布局 Ctrl+L

一 基本布局管理器 QBoxLayout      layout 

	margin 边界 空白

	layoutName  			布局管理器 名字
	layoutLeftMargin		布局管理器到左边界的距离
	layoutTopMargin			布局管理器到上边界的距离
	layoutRightMargin		布局管理器到右边界的距离
	layoutBottomMargin		布局管理器到下边界的距离
	layoutSpacing			布局管理器中各个子部件的距离
	layoutStretch			伸缩因子
	layoutSizeConstraint	设置大小的约束条件

	new layout  --->  addWidget ---> setSpacing and so on ---> setLayout 
	
二 栅格布局管理器 QGridLayout
	void QGridLayout::addWidget(QWidget *widget, int fromRow, int fromColumn,
				int rowSpan, int columnSpan, Qt::Alignment alignment = Qt::Alignment())
	 fromRow  	从行号 开始  行号从0开始计算    0  1  2  
	 fromColumn 从列号 开始  列号从   			0  1  2
	 rowSpan    占几行							0  1  2
	 columnSpan	占几列
	 
三 表单布局管理器
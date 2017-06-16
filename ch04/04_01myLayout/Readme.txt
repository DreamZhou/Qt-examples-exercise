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
	 
三 表单布局管理器 QFormLayout
	用来管理表格的输入部件及相关标签，设置伙伴关系，
	伙伴关系 ：将两个不同部件关联在一起（前提是二者可以关联）之后，
		它们也就有了一个类似伙伴的关系，把窗口焦点移动到其中一个对象时会自动切换到它的伙伴对象。

四 设置部件大小
	大小提示(sizeHint) 				部件的建议大小   	sizeHint()  来获取
	最小大小提示(minimumSizeHint)	部件的建议最小大小	minimumSizeHint() 来获取，
									如设置minimumSize，则忽略minimumSizeHint。
	大小测量(sizePolicy)
	QSizePolicy::Fixed				只能使用 sizeHint() 的值，无法伸缩。
	QSizePolicy::Minimum			sizeHint()的值是最小，可以被拉伸
	QSizePolicy::Maximum			sizeHint()的值是最大，可以被压缩
	QSizePolicy::Preferred			sizeHint()的值是最佳，可以被拉伸/压缩
	QSizePolicy::Expanding			sizeHint()的值是合适，可以被拉伸/压缩，倾向拉伸
	QSizePolicy::MinimumExpanding	sizeHint()的值是最小，倾向拉伸
	QSizePolicy::Ignorred			sizeHint() 的值被忽略，倾向拉伸
		
		
		
		
		
		
		
		
		
		
		
		

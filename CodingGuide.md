# 序言

为统一开发部所有成员的代码规格，以方便阅读、理解，特指定本指南。由于开发语言的多样性和复杂性，也由于时间所限，本指南不可能涵盖所有情况。因此留待大家讨论和补充。代码风格的本质是使代码容易理解，因此一切关于本指南的改进不应该脱离于这种本质的要求。

本指南以C++为主要说明对象。

# 命名规则

命名采用**匈牙利命名法**，以chBoundSameDensity为例，ch表示char变量，然后以一连串首字母大写的单词表述变量的意义。取名的意义十分重大，需要认真对待。因为固然你可以加一个说明解释变量的意义，但都不及一个好名字来得方便。代码的最高境界是不需注释就能明白代码的意义（当然一个精巧的算法应该用注释说明，一个公式也应该注释说明，因为此时只靠命名不能解决阅读问题）。
若命名过长，可适当考虑使用一些缩写，但缩写的原则应以仍能见名知意为准，否则就不应使用缩写。例如Button缩写为Btn是容易理解的。而自创的缩写往往是不容易（被别人）理解的。

* 1 一般变量、函数参数变量的命名：变量类型前缀+变量名，变量类型的前缀如下，注意前缀为小写：

     char/TCHAR        ch     --字符型
     int                  i      --整型
     short/INT16          o      --短整型数
     float                f       --单精度浮点数
     double              d       --双精度浮点数
     HANDLE            h       --windows句柄 
     DWORD            dw     --字
     bool/BOOL           b       --布尔量，建议除了WINDOWS的API                                    函数常用BOOL外，其它均采用bool。
     enum                e       --枚举
     char[]               sz       --字符串数组 
     其他数组            在变量的结尾加后缀s(小写，表示复数，多个之意)

* 2 指针变量在1的基础上加前缀p。

* 3 类对象变量：
     一般类对象变量在1的基础上加前缀c
     常见MFC对象前缀命名如下
     CString        s
     CEdit          cEdt
     CButton        cBtn
     CStatic         CStatic若显示字符串用m_cLab，若显示图像用m_cImg
     CListBox       cLbx
     CList          cLst
     CComboBox    cCmb
     CDialog        dlg 
     CPen          cPen
     ........

* 4 临时变量可加前缀tmp。

* 5 成员变量的命名在1，2，3的基础上加前缀m_。

* 6 全局变量的命名在1，2，3的基础上加前缀g_。

* 7 资源命名全部采用大写，其中类型不简写，含义段若开发文档已经给予了对应的变量名，可将变量名大写作为其含义段，例如：
IDC_CHECK_NOSHOWCONSAMEBEAMSTEEL，前面的IDC_CHECK是控件放在窗口上时就缺省有的，后跟‘_’+NOSHOWCONSAMEBEAMSTEEL，是对应变量m_bNoShowConSameBeamSteel的‘NoShowConSameBeamSteel’（选中字符串，按Ctrl+Shift+U可转换为大写）。资源名不能随意命名，或者采用缺省的IDC_CHECK1，IDC_CHECK2等等。注意我们的程序是要见名知意，一切无意义的表达都应尽量避免。
    常用的资源类型有：
        按钮    IDC_BUTTON_
        复选框  IDC_CHECK_
        单选框  IDC_RADIO_
        下拉框  IDC_ COMBO_
        列表框  IDC_LIST_
        编辑框  IDC_EDIT_
        对话框  IDD_DIALOG_
        菜单    IDR_MENU_
        右键菜单IDR_POP_MENU_
        工具条  IDR_TOOLBAR_  

* 8 函数的命名：
函数的命名也采用匈牙利命名法，即以一连串首字母大写的单词表述变量的意义。此时不需要在前面加前缀去表明函数的返回值！例如， IsSame()函数，就没有必要写成 bIsSame()，因为IsSame已经明确表达了是和否的概念，因此理应返回一个bool 量。不重复地表达同一个概念，应该也成为命名的一个原则。
函数的形参定义放在后面描述。
事件函数的命名，一般以MFC自动生成的代码为准。

* 9 类的命名
类以C开头，同样采用匈牙利命名法；如果是子类，可采用前缀的方法去表明：例如CSection是截面类，CRectSect是矩形截面类 

# 编码的行文风格

编码就像写文章，要自然段清晰。每一件事为一段，中间以空行分开。每一段若不清楚可加若干注释。但要注意，代码的最高境界是无需注释（代码应该成为你的第二语言，而不需要加翻译），因此首要是代码清晰、简明，其次才是加注释。

如何使代码清晰？需要遵循一定的原则。

* 1 代码应该排版，层次清晰，例如有了‘{’后应该换行缩进。如果代码已经乱了，可选择要排版的自然段，按Ctrl+K，Ctrl+F自动排版（VC6中按Alt+F8）；
   有时会发现排版不起作用，例如一下情况：
        ACRX_DXF_DEFINE_MEMBERS (
			CAColZhongSteel, AcDbObject,
			AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
			AcDbProxyEntity::kNoOperation, GBACOL,
			 "GSPLOTAPP"
			 "|Product Desc:     XXXX"
			 "|Company:          XXXX"
			 "|WEB Address:      www.xxxx.com.cn"
			 )
    上述是一段宏，注意这个宏结尾是不需加;，因为宏展开以后的代码是有;号结尾的。但是排版程序不能识别宏的语句，导致排版后，宏的下一行在宏的结尾处对齐。处理这种情况，可以在这个宏结尾加一个;，这不会引起语法错误，实际上就是加了一句空语句，在RELEASE版本中，编译器会优化掉，也不会有性能的损失。
    又例如，goto语句（虽然不提倡用）转到的标签行，应该在标签行后另起一行写代码，就能得到正确的排版。
    .......

    
* 1 代码的缩进层次，一般来说不应超过3层。当缩进层次多了以后，不移动水平滚动条就无法看到代码，十分不便。实际上这种多层缩进是可以解开的。例如下面代码：
if(OldFile.Open(m_szFileName, CFile::modeRead|CFile::typeText|CFile::shareDenyNone, NULL) )
{
   ...........
}
实际上可以写成
if(!OldFile.Open(m_szFileName, CFile::modeRead|CFile::typeText|CFile::shareDenyNone, NULL) )
{
	AfxMessageBox("ChangTimeTemp open error!");
	return ;
}
.........

这样打开文件成功后的代码（一般肯定比错误处理代码更长）就可以不缩进了。

另外，如果缩进过多，某种程度上说明本函数干得过多，把应该另起一个函数的内容写在了本函数。即最内层的几层缩进可以用一个函数来代替。

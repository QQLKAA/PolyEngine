#include "PolyEditorPCH.hpp"

class LoggerWidget;

class EditorOutputStream : public Poly::FileOutputStream
{
public:
	EditorOutputStream(const char* name, LoggerWidget* widget)
		: FileOutputStream(name)
	{
		Logger = widget;
	}

	void Append(const char* data) override
	{
		Logger->AppendLog(data);
		Poly::FileOutputStream::Append(data);
	}
private:
	LoggerWidget* Logger = nullptr;
};


LoggerWidget::LoggerWidget(eLoggerType type)
{
	Layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight, this);
	TextEdit = new QTextEdit(this);
	TextEdit->setReadOnly(true);
	Layout->addWidget(TextEdit);

	switch (type)
	{
	case eLoggerType::CONSOLE:
		Poly::gConsole.RegisterStream<EditorOutputStream>("console.log", this);
		break;
	case eLoggerType::CMD:
		gApp->CmdMgr->RegisterStream<EditorOutputStream>("cmd.log", this);
		break;
	default:
		break;
	}
}

LoggerWidget::~LoggerWidget()
{
	Poly::gConsole.RegisterDefaultStream();
}

void LoggerWidget::AppendLog(const char * data)
{
	TextEdit->moveCursor(QTextCursor::End);
	TextEdit->insertPlainText(QString::fromLocal8Bit(data));
	TextEdit->moveCursor(QTextCursor::End);
	TextEdit->show();
}

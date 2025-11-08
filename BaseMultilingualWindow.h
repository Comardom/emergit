#ifndef EMERGIT_BASEMULTILINGUALWINDOW_H
#define EMERGIT_BASEMULTILINGUALWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QMenu>
#include <QActionGroup>
#include <QMenuBar>

QT_BEGIN_NAMESPACE
namespace Ui {
	class BaseMultilingualWindow;
}
QT_END_NAMESPACE

class BaseMultilingualWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit BaseMultilingualWindow(QWidget *parent = nullptr);
	~BaseMultilingualWindow() override;

protected:
	void changeEvent(QEvent *event) override;
	void createLanguageMenu(); // 创建多语言菜单

private slots:
	void changeLanguage(QAction *action);

private:
	Ui::BaseMultilingualWindow *ui;
	QTranslator appTranslator; // 用于管理当前加载的翻译器
	QActionGroup *langActionGroup; // 用于管理菜单项的互斥选择
	void loadTranslator(const QString &localeName);
};

#endif // EMERGIT_BASEMULTILINGUALWINDOW_H

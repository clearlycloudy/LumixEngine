#pragma once


#include <QDockWidget>


namespace Lux
{
	class EditorClient;
	class PipelineInstance;
}

namespace Ui
{
	class GameView;
}

class GameView : public QDockWidget
{
	Q_OBJECT

public:
	explicit GameView(QWidget* parent = NULL);
	virtual ~GameView();

	QWidget* getContentWidget() const;
	void setPipeline(Lux::PipelineInstance& pipeline) { m_pipeline = &pipeline; }
	void setEditorClient(Lux::EditorClient& client) { m_client = &client; }

private slots:
	void on_playButton_clicked();

private:
	virtual void resizeEvent(QResizeEvent*) override;

private:
	Ui::GameView* m_ui;
	Lux::PipelineInstance* m_pipeline;
	Lux::EditorClient* m_client;
};

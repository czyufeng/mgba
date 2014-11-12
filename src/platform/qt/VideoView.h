#ifndef QGBA_VIDEO_VIEW
#define QGBA_VIDEO_VIEW

#ifdef USE_FFMPEG

#include <QWidget>

#include "ui_VideoView.h"

extern "C" {
#include "platform/ffmpeg/ffmpeg-encoder.h"
}

namespace QGBA {

class VideoView : public QWidget {
Q_OBJECT

public:
	struct Preset {
		QString container;
		QString vcodec;
		QString acodec;
		int vbr;
		int abr;
		int width;
		int height;

		bool compatible(const Preset&) const;
	};

	VideoView(QWidget* parent = nullptr);
	virtual ~VideoView();

	GBAAVStream* getStream() { return &m_encoder.d; }

public slots:
	void startRecording();
	void stopRecording();

signals:
	void recordingStarted(GBAAVStream*);
	void recordingStopped();

private slots:
	void selectFile();
	void setFilename(const QString&);
	void setAudioCodec(const QString&, bool manual = true);
	void setVideoCodec(const QString&, bool manual = true);
	void setContainer(const QString&, bool manual = true);

	void setAudioBitrate(int, bool manual = true);
	void setVideoBitrate(int, bool manual = true);

	void setWidth(int, bool manual = true);
	void setHeight(int, bool manual = true);
	void setAspectWidth(int, bool manual = true);
	void setAspectHeight(int, bool manual = true);

	void showAdvanced(bool);

	void uncheckIncompatible();

private:
	bool validateSettings();
	void updateAspectRatio(int width, int height, bool force = false);
	static QString sanitizeCodec(const QString&, const QMap<QString, QString>& mapping);
	static void safelyCheck(QAbstractButton*, bool set = true);
	static void safelySet(QSpinBox*, int value);
	static void safelySet(QComboBox*, const QString& value);

	void addPreset(QAbstractButton*, const Preset&);
	void setPreset(const Preset&);

	Ui::VideoView m_ui;

	FFmpegEncoder m_encoder;

	QString m_filename;
	QString m_audioCodec;
	QString m_videoCodec;
	QString m_container;
	char* m_audioCodecCstr;
	char* m_videoCodecCstr;
	char* m_containerCstr;

	int m_abr;
	int m_vbr;

	int m_width;
	int m_height;

	QMap<QAbstractButton*, Preset> m_presets;

	static QMap<QString, QString> s_acodecMap;
	static QMap<QString, QString> s_vcodecMap;
	static QMap<QString, QString> s_containerMap;
};

}

#endif

#endif

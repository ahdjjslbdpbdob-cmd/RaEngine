#ifndef PROJECTWIZARDDIALOG_H
#define PROJECTWIZARDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class ProjectWizardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectWizardDialog(QWidget *parent = nullptr);

    QString projectName() const;
    QString quality() const;
    QString savePath() const;

private slots:
    void onBrowse();

private:
    QLineEdit *nameEdit;
    QComboBox *qualityCombo;
    QLineEdit *pathEdit;
    QPushButton *browseBtn;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
};

#endif // PROJECTWIZARDDIALOG_H
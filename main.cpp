#include <QCoreApplication>
#include <QVector>
#include <QDir>
#include <QDebug>
#include <QList>
#include <QString>

//opencv includes
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"



// load the image files for this demo from the folder name/path and output each image into a directory;
int fs_shuffleFiles(QString inputDirectory, QString outputDirectory)
{
    QList<cv::Mat> mats, shuffled;
    QVector<QString> filenames;
    qDebug() << inputDirectory;
    cv::Mat im;


    QDir dir(inputDirectory);
    if (!dir.exists())
        qWarning("Cannot find the input directory");

    QDir dirOut(outputDirectory);
    if (!dirOut.exists())
        qWarning("Cannot find the output directory");

    //set the filter and sorting flags for entryInfoList()
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    QFileInfoList list = dir.entryInfoList(); // sorted by name
    QFileInfoList selected;

//select the files of stated filetype.
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QString fs = fileInfo.fileName();
        if (fs.endsWith(".bmp") || fs.endsWith(".png") || fs.endsWith(".jpg"))
        {
            filenames.push_back(fs);
            selected.push_back(list.at(i));
            qDebug() << i << "  file name  " << fs;
        }
    }
//get the absolute file path of the image file and convert to cv::Mat
    for (int i = 0; i < selected.size(); ++i)
    {
       QFileInfo fileInfo = selected.at(i);
       QString fs = fileInfo.absoluteFilePath();
       im = cv::imread(fs.toStdString());
       mats.push_back(im);
    }


    while (mats.size() != 0)
    {
        int randomIndex = rand() % mats.size();
        shuffled.push_back(mats[randomIndex]);
        mats.erase(mats.begin()+(randomIndex));
    }

    for(int i = 0; i < shuffled.size(); ++i)
    {
        QString file = outputDirectory + "/image" + QString::number(i) +".png";
        try
        {
            imwrite(file.toStdString(), shuffled[i]);
        }
        catch (cv::Exception& ex)
        {
            fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
            return 1;
        }
        fprintf(stdout, "Saved PNG file.\n");
    }
    return 0;
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int i = fs_shuffleFiles("/home/chs/workspace/testImages/lenas", "/home/chs/workspace/testImages/shuffledImages");

    return 0;
    return a.exec();

}

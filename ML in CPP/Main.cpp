#include "DataHandler.h"
#include "KNN.h"
int main()
{
	DataHandler dh("../train_images.bin", "../train_labels.bin");
    KNN knn(3);//k = 1 by default
    knn.validatePerformance();
    //Finding Best k
    //float performance = 0;
    //float best_performance = 0;
    //int best_k = 1;
    //for (int k = 1; k <= 3; k++)
    //{
    //    if (k == 1)
    //    {
    //        performance = knn.validatePerformance();
    //        best_performance = performance;
    //    }
    //    else
    //    {
    //        knn.setK(k);
    //        performance = knn.validatePerformance();
    //        if (performance > best_performance)
    //        {
    //            best_performance = performance;
    //            best_k = k;
    //        }
    //    }
    //}
    //knn.setK(best_k);
    //knn.testPerformance();
    getchar();
}
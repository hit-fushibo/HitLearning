import numpy as np

def k_means(data, k, max_iters=100):
    # 随机选择k个初始聚类中心
    centroids = data[np.random.choice(range(len(data)), k, replace=False)]
    
    for _ in range(max_iters):
        # 计算每个样本与各个聚类中心的距离
        distances = np.linalg.norm(data[:, np.newaxis] - centroids, axis=2)
        
        # 分配样本到最近的聚类中心
        labels = np.argmin(distances, axis=1)
        
        # 更新聚类中心
        new_centroids = np.array([data[labels == i].mean(axis=0) for i in range(k)])
        
        # 如果聚类中心不再变化，则停止迭代
        if np.all(centroids == new_centroids):
            break
        
        centroids = new_centroids
    
    return labels, centroids

# 示例用法
data = np.random.normal(0,8,(1500000,20))
k = 2

labels, centroids = k_means(data, k)

print("聚类结果：")
for i in range(k):
    cluster_data = data[labels == i]
    print(f"聚类中心 {i+1}: {centroids[i]}")
    # print(f"所属样本：{cluster_data}")
    # print()

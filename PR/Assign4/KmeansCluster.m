classdef KmeansCluster < handle
    %KMeans Clusting
    % partitions the points in the nXm data matrix into K clusters
    % Usage example:
    %   KM = KmeansCluster(3); %3 = no of mixtures
    %   KM.train(c);          %c = input Vectors
    %   KM.Kmeans       %to get Means
    %   KM.Kvariance    %to get Variance
    %   KM.getLabel(ip) % get label of `ip` vector
    %
    
    properties (SetAccess = public)
        K; % No: of Clusters
        Kmeans; % Means of Clusters
        Kvariance; % Covariances of Clusters
    end
    
    methods
        function obj = KmeansCluster(k)
            %constructor:set K (No: of Clusters)
            %Usage: obj = KmeansCluster(k);
            %Parameter:
            %   k - # of Clusters
            %
            obj.K = k;
        end %constructor
        
        function train(obj,inputVectors,stepCount)
            %Train k-means clusting
            %Usage:
            %   obj.train(inputVectors);
            %   obj.train(inputVectors,stepCount);
            %Parameters:
            % inputVectors - input Vectors (MxN)
            % stepCount (optional) - Maxium no of iteration
            %       default value = 15
            if(nargin==2)
                stepCount = 15;
            end
            [M,N] = size(inputVectors);
            classLabel = randi(obj.K,1,M);
            obj.Kmeans=zeros(obj.K,N);
            obj.Kvariance=zeros(N,N,obj.K);
            %init Random mean
            for trail = 1:5
                for j = 1:obj.K
                    obj.Kmeans(j,:) = mean(inputVectors(classLabel==j,:));
                end
                i=0;
                threshold = 0.001;
                meanError = threshold +1;
                while (i < 2 || (meanError > threshold && i < stepCount ))
                    i=i+1;
                    %E step
                    
                    if(i<12)
                        %euclidean distance
                        for j = 1:M
                            classLabel(j) = obj.getLabel(inputVectors(j,:),true);
                        end
                    else
                        s = warning('off','all');
                        %Mahalanobis distance
                        for j = 1:M
                            classLabel(j) = obj.getLabel(inputVectors(j,:),false);
                        end
                        warning(s);
                    end
                    %M step
                    KmeanOld = obj.Kmeans;
                    for j = 1:obj.K
                        classVectors = inputVectors(classLabel==j,:);
                        obj.Kmeans(j,:) = mean(classVectors);
                        obj.Kvariance(:,:,j) = cov(classVectors);
                    end
                    meanError = norm(obj.Kmeans-KmeanOld);
                end
                if sum(isnan(obj.Kmeans))== 0
                    break;
                end
            end
            fprintf('After %d iteration\n',i);
        end
        
        function [ label ] = getLabel(obj,inputVector,euclidean)
            %Find label of input Vector
            %Usage:
            %   obj.getLabel(inputVector);
            %   obj.getLabel(inputVector,euclidean)
            %parameters:
            % inputVector - input Vector to be labeled
            % euclidean (optional) -
            %       if `true` distance measure is euclidean
            %       else distance measure is Mahalanobis distance
            %       default value :true
            
            if(nargin <3)
                euclidean = true;
            end
            k = obj.K;
            diffVector = bsxfun(@minus,obj.Kmeans,inputVector);
            if euclidean
                distances = sqrt(sum(diffVector.*diffVector,2));
            else
                distances = zeros(1,k);
                for i = 1:k
                    distances(i) = sqrt(diffVector(i,:)/obj.Kvariance(:,:,i)*diffVector(i,:)');
                end
            end
            [~,label] = min(distances);
        end
    end
end

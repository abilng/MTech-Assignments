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
    properties (Hidden)
       cmap; %Color for ploting
    end
    
    methods
        function obj = KmeansCluster(k)
            %constructor:set K (No: of Clusters)
            %Usage: obj = KmeansCluster(k);
            %Parameter:
            %   k - # of Clusters
            %
            obj.K=k;
            obj.cmap = hsv(k);
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
            %Note:
            %   if N =2 ie, Vectors are of 2 Diamentional,
            %   It also plot training step
            %
            if(nargin==2)
                stepCount = 15;
            end
            [M,N] = size(inputVectors);
            classLabel = randi(obj.K,1,M);
            obj.Kmeans=zeros(obj.K,N);
            obj.Kvariance=zeros(N,N,obj.K);
            if (N == 2)
                figure;
                KmeansScatter=zeros(1,obj.K);
            end
            %init Random mean
            for j = 1:obj.K
                obj.Kmeans(j,:) = mean(inputVectors(classLabel==j,:));
                if (N == 2)
                    KmeansScatter(j) = plot(obj.Kmeans(j,1),obj.Kmeans(j,2), ...
                        'kx','MarkerFaceColor',obj.cmap(j,:), 'MarkerSize',12, ...
                        'LineWidth',2,'MarkerEdgeColor','black');
                    hold on;
                end
            end
            i=0;
            threshold = 0.001;
            meanError = threshold +1;
            while (i < 2 || (meanError > threshold && i < stepCount ))
                i=i+1;
                %E step
                
                if(i<10)
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
                    if (N==2)
                        scatter(classVectors(:,1),classVectors(:,2),...
                            '*','CData',obj.cmap(j,:));hold on;
                        delete(KmeansScatter(j));
                        KmeansScatter(j) = plot(obj.Kmeans(j,1),obj.Kmeans(j,2), ...
                            'kx','MarkerFaceColor',obj.cmap(j,:),'MarkerSize',12, ...
                            'LineWidth',3,'MarkerEdgeColor','black');

                    end
                end
                meanError = norm(obj.Kmeans-KmeanOld)
                if (N==2)
                    pause(0.5);
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
            %       if `true` distance mesaure is euclidean
            %       else distance mesaure is Mahalanobis distance
            %       default value :true
            
            if(nargin <3)
                euclidean = true;
            end
            k = obj.K;
            distaces = zeros(1,k);
            for i = 1:k
                diffVector = inputVector - obj.Kmeans(i,:);
                if euclidean
                    distaces(i) = norm(diffVector);
                else
                    distaces(i) = sqrt(diffVector/obj.Kvariance(:,:,i)*diffVector');
                end
            end
            [~,label] = min(distaces);
        end
    end
end

classdef GMM < handle
    %GMM Summary of this class goes here
    %   Detailed explanation goes here
    % Usage example:
    %   G = GMM(3);         %3 = no of mixtures
    %   G.train(c)          %c = input Vectors
    %   G.mixureMeans       %to get Means
    %   G.mixureVariance    %to get Variance
    %
    %
    
    properties (SetAccess = public)
        K; % No: of Mixures
        mixureMeans; % Means of Mixures
        mixureVariance; % Covariances of Mixures
        pi; %pi(k) = N(k)/sum(N(k))
    end
    properties (Hidden)
        KM;
    end
    
    methods
        function obj = GMM(k)
            %set K (No: of Mixure)
            %obj = GMM(k)
            %parameters:
            %   k - no of mixture
            obj.K = k;
            obj.pi = zeros(1,k);
            obj.KM = KmeansCluster(k);
        end %constructor
        
        function resetK(obj,k)
            %parameters:
            %   k - no of mixture
            obj.K = k;
            obj.pi = zeros(1,k);
            obj.KM = KmeansCluster(k); 
        end
        
        function train(obj,inputVectors)
            %Train GMM
            %Usage: obj.train(inputVectors)
            %parameters:
            % inputVectors - input Vectors (MxN)
            %
            %[M,~] = size(inputVectors);
            [M,N] = size(inputVectors);
            obj.KM.train(inputVectors,12);
            obj.mixureMeans=obj.KM.Kmeans;
            obj.mixureVariance= obj.KM.Kvariance;
            gama = zeros(M,obj.K);
            
            for j = 1:M
                gama(j,obj.KM.getLabel(inputVectors(j,:))) = ...
                    gama(j,obj.KM.getLabel(inputVectors(j,:))) +1;
            end
            obj.pi = sum(gama)./M;
            
            
            for i =(1:3)
                %E step
                for j = 1:M
                    gama(j,:) = obj.getResp(inputVectors(j,:));
                end
                %M step
                Mk = sum(gama);
                for k = 1:obj.K
                    var = zeros(N,N);
                    %for j = 1:M
                    %    mean = mean + inputVectors(j,:).*gama(j,k);
                    %end
                    mean = sum(bsxfun(@times,inputVectors,gama(:,k)));
                    mean = mean./Mk(k);
                    diffVector = bsxfun(@minus,inputVectors,mean);
                    %diff_Gama = bsxfun(@times,diff,gama(:,k));
                    %var = diff(j,:)'*diff_Gama(j,:);
                    for j = 1:M
                        var = var + diffVector(j,:)'*diffVector(j,:).*gama(j,k);
                    end
                    var = var./Mk(k);
                    obj.mixureMeans(k,:) = mean;
                    obj.mixureVariance(:,:,k) = var;
                end
                obj.pi = Mk./M;
            end
        end
        
        function [ resp ] = getResp(obj,inputVector)
            %Find responsibility of input Vector
            %Usage: obj.getResp(inputVector)
            %parameters:
            % inputVector - input Vector whose responsibility to find
            %
            k = obj.K;
            resp = zeros(1,k);
            for i = 1:k
                resp(i) = mvnpdf(inputVector, ...
                    obj.mixureMeans(i,:),obj.mixureVariance(:,:,i));
            end
            resp = resp.*obj.pi;
            respTotal = sum(resp);
            resp = resp./respTotal;
        end
        
        function [ probability ] = getLikelihood(obj,inputVector,naiveBayes)
            %Find probability of input Vector
            %Usage: obj.getProbability(inputVector)
            %parameters:
            % inputVector - input Vector whose Probability to find
            % naiveBayes(optional) - boolean [default value ='false']
            %
            if (nargin == 2)
                naiveBayes = false;
            end
            
            k = obj.K;
            probability = zeros(1,k);
            
            if (naiveBayes)
                for i = 1:k
                    probability(i) = mvnpdf(inputVector,obj.mixureMeans(i,:), ...
                        diag(diag(obj.mixureVariance(:,:,i))));
                end
            else
                for i = 1:k
                    probability(i) = mvnpdf(inputVector,obj.mixureMeans(i,:), ...
                        obj.mixureVariance(:,:,i));
                end
            end
            probability = probability.* obj.pi;
            probability = log(sum(probability));
        end
    end
end
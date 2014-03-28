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
            
            obj.K=k;
            obj.pi = zeros(1,k);
            obj.KM = KmeansCluster(k);
        end %constructor
        
        function train(obj,inputVectors)
            %Train GMM
            %Usage: obj.train(inputVectors)
            %parameters:
            % inputVectors - input Vectors (MxN)
            %
            %if N =2 ie, Vectors are of 2 Diamentional,
            %   It also plot training step
            
            [M,N] = size(inputVectors);
            obj.KM.train(inputVectors,10);
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
                    mean = zeros(1,N);
                    var = zeros(N,N);
                    for j = 1:M
                        mean = mean + inputVectors(j,:).*gama(j,k);
                    end
                    mean = mean./Mk(k);
                    for j = 1:M
                        var = var + ((inputVectors(j,:)-mean)'*(inputVectors(j,:)-mean)).*gama(j,k);
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
                resp(i) = obj.pi(i)*mvnpdf(inputVector, ...
                    obj.mixureMeans(i,:),obj.mixureVariance(:,:,i));
            end
            respTotal = sum(resp);
            resp = resp./respTotal;
        end
        function [ probability ] = getProbability(obj,inputVector)
            %Find probability of input Vector
            %Usage: obj.getProbability(inputVector)
            %parameters:
            % inputVector - input Vector whose Probability to find
            %
            k = obj.K;
            probability = 0;
            for i = 1:k
                probability= probability + ...
                    obj.pi(i)*mvnpdf(inputVector,obj.mixureMeans(i,:),obj.mixureVariance(:,:,i));
            end
        end
    end
end
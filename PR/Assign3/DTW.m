classdef DTW <handle
    %DTW  Dynamic Time Warping (DTW)
    %   for measuring similarity between two temporal sequences
    %   Detailed explanation goes here
    
    properties(SetAccess = public)
        refVector;
    end
    properties(Hidden)
        n;
    end
    
    methods
        function [obj] = DTW()
            obj.n = 0;
        end
        
        function setReference(obj,refVector)
            obj.refVector = refVector;
            [obj.n,~] = size(refVector);
        end
        
%         function trainReference(obj,refVectors)
%             meanVector = refVectors;
%             obj.setReference(meanVector)
%         end
        
        function [DTWdist] = DTWDistance(obj,testVector)
            [m,~] = size(testVector);
            DTWtable = Zeros(obj.n+1,m+1);
            DTWtable(:,1) = Inf;
            DTWtable(1,:) = Inf;
            DTWtable(1,1) = 0 ;
            
            for i = 2:obj.n+1
                for j = 2:m+1
                    cost= norm(obj.refVector(i-1,:), testVector(j-1,:));
                    DTWtable (i,j) = cost + minimum(DTWtable(i-1,j), DTWtable(i,j-1),DTWtable(i-1,j-1));
                end
            end
            DTWdist = DTWtable(obj.n, m);
        end
        
    end
end
    

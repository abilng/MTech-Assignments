%% Parzen Window
%
%%
function [ class ] = parzenWindow(testVectors,refVectors,refLabel,h,C,type)
%parzenWindow Parzen Window Classifer
%
%Input
% testVectors
% refVectors
% refLabel
% h
% C
% type
%
%Output:
% loglikhood

likelihood = zeros(1,C);

switch(type)
    case 'hypersphere'
        windows = rangesearch(refVectors,testVectors,h);
        for j = 1:size(testVectors,1)
            prob = ones(1,C);
            window = windows{j};
            K = size(window,2)+1;
            windowLabels = refLabel(window);
            prob = prob + sum(bsxfun(@eq,windowLabels,1:C),1);
            prob = prob./K;
            prob = log(prob);
            likelihood = likelihood + prob;
        end
        
    case 'gaussian'
        [N,d] = size(testVectors);
        denominator = (2*pi*h*h)^(d/2);
        for i = 1:N
            prob = zeros(1,C);
            for j = 1:C
                classPoints = refVectors(refLabel == j,:);
                exponent = bsxfun(@minus,classPoints,testVectors(i,:));
                exponent = exponent./h;
                exponent = sum((exponent.*exponent),2)./2;
                prob(j) = sum(exp(-exponent))/denominator;
            end
            K = size(refVectors,1);
            prob = log(prob./K);
            likelihood = likelihood + prob;
        end
    otherwise
        error('Unknown option');
end;
[~,class] = max(likelihood);
end

%%
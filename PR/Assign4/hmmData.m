% HMM code for Handwritten dataset
function [classNo, classList, data] = hmmData()

if exist('../data/hmm/handwritten','dir')
    dataPath = '../data/hmm/handwritten';
else
    dataPath = uigetdir;
end

classList = dir(dataPath);
classList = {classList(~strncmpi({classList.name},'.',1)).name};
classNo = size(classList,2);
data{classNo} = {};

for i = 1:classNo
    fId = fopen(char(strcat(dataPath,'/',classList(i))));
    line1 = fgets(fId);
    j = 1;
    while ischar(line1)
        line2 = fgets(fId);
        line3 = fgets(fId);
        [~,line3] = strtok(line3);
        line3 = reshape(str2num(line3),2,[])';
        
        % Feature : Slope (but inf values, so not taking)
        % ftr = diff(reshape(str2num(line3),2,[])');
        % ftr = (ftr(:,2)./ftr(:,1))';
        
        % Feature1 : Normalized X-Y Coordinates b/w [0,1]
        line3(:,1) = bsxfun(@minus,line3(:,1),min(line3(:,1)))./(max(line3(:,1))-min(line3(:,1)));
        line3(:,2) = bsxfun(@minus,line3(:,2),min(line3(:,2)))./(max(line3(:,2))-min(line3(:,2)));
        ftr(:,1:2) = line3;
        
        % Feature2 : Normalized First Derivatives
        tmpArray = padarray(line3,[2 0]);
        tmp = 2*circshift(tmpArray,[-2,0]);
        tmp = tmp + circshift(tmpArray,[-1,0]);
        tmp = tmp - circshift(tmpArray,[1,0]);
        tmp = tmp - 2*circshift(tmpArray,[2,0]);
        tmp = tmp/10;
        ftr(:,3:4) = tmp(3:end-2,:);
        
        % Feature3 : Normalized Second Derivatives
        tmpArray = padarray(ftr(:,3:4),[2 0]);
        tmp = 2*circshift(tmpArray,[-2,0]);
        tmp = tmp + circshift(tmpArray,[-1,0]);
        tmp = tmp - circshift(tmpArray,[1,0]);
        tmp = tmp - 2*circshift(tmpArray,[2,0]);
        tmp = tmp/10;
        ftr(:,5:6) = tmp(3:end-2,:);
        
        % Feature4 : Curvature
        % x'.y'' - x''.y'/((x'^2+y'^2)^(3/2))
        %numerator = ftr(:,3).*ftr(:,6)-ftr(:,5).*ftr(:,4);
        %denominator = (sum(ftr(:,3:4).^2,2)).^(3/2);
        %ftr(:,7) = numerator./denominator;
        
        line1 = fgets(fId);
        data{i}{j} = ftr;
        j = j + 1;
        clear ftr;
    end
    
    fclose(fId);
end
clear ans dataPath denominator fId i j line1 line2 line3 num numerator tmp tmpArray
end
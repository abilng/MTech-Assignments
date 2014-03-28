close all
clear all
clc

IMGPATH = 'C../Yogi.gif';

[inImage,map] = imread(IMGPATH);
inImage = ind2rgb(inImage, map);
inImage=rgb2gray(inImage);

minSVal = input('Enter the minimum number of Singular Value:');
step = input('Enter the step of Singular Value:');
maxSVal = input('Enter the max number of Singular Value:');


reply = input('Do you want display each img? Y/N [Y]: ', 's');
if isempty(reply)|| strcmp(reply,'Y') || strcmp(reply,'y') 
    display = true;
else 
    display = false;
end

% decomposing the image using singular value decomposition
[U,S,V]=svd(inImage);

numSVals = minSVal:step:maxSVal;

dispEr = [];
for k= numSVals

    C = S;
    % discard the diagonal values not required for compression
    C(k+1:end,:)=0;
    C(:,k+1:end)=0;

    % Construct an Image using the selected singular values
    D=U*C*V';
    %compute error
    errorImg = abs(D-inImage);
    
    % display
    if(display)
        figure;
        buffer = sprintf('Image output using %d singular values', k);
        subplot(1,2,1);
        imshow(D);
        title(buffer);
        subplot(1,2,2);
        imshow(errorImg);
        title('Error Image');
    end
    
    error = norm(errorImg,'fro');
    % store vals for display
    dispEr = [dispEr; error];
end

figure; 
title('Error in compression');
plot(numSVals, dispEr);
grid on
xlabel('Number of Singular Values used');
ylabel('Error between compress and original image');


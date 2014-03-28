clear all
clc

IMGPATH = '../DSC01934.jpg';
inImage=imread(IMGPATH);
inImage=rgb2gray(inImage);

inImage = im2double(inImage);
% decomposing the image using singular value decomposition
[U,S,V]=svd(inImage);

k = input('Enter No of Singular Values');

% discard the diagonal values not required for compression
S(k+1:end,:)=0;
S(:,k+1:end)=0;

% Construct an Image using the selected singular values
D=U*S*V';
errorImg = inImage-D;
% display
buffer = sprintf('Image_3_%d.jpg', k);
imwrite(uint8(D),buffer);
buffer = sprintf('Image_3_er_%d.jpg', k);
imwrite(uint8(errorImg),buffer);

error=norm(errorImg,'fro');

buffer = sprintf('Error is = %d',error);
disp(buffer);
function prob = kNearN(testVector,refVectors,refLabel,k,C)

N = size(refVectors,2);
prob = ones(1,C);
[~,window] = pdist2(refVectors,testVector,'euclidean','Smallest',k);
K = size(window,2)+1;
windowLabels = refLabel(window);
prob = prob + sum(bsxfun(@eq,windowLabels,1:C),1);
prob = prob./K;
prob = log(prob);
if N == 2
    %plot data
    cmap = hsv(C);
    for j = 1:C
        class = refVectors(refLabel == j,:);
        scatter(class(:,1),class(:,2),...
            '*','CData',cmap(j,:));hold on;
    end
    [~,class] = max(prob);
    plot(testVector(1),testVector(2), ...
        'kx','MarkerSize',12, ...
        'LineWidth',3,'MarkerEdgeColor','black');
    viscircles(testVector,h,'EdgeColor',[1 1 1]-cmap(class,:));
end

end
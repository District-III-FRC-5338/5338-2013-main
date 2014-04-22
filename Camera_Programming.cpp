//Camera constants used for distance calculation 
#define Y_IMAGE_RES 480     //X Image resolution in pixels, should be 120, 240 or 480
#define VIEW_ANGLE 49       //Axis M1013
//#define VIEW_ANGLE 48     //Axis M1013 camera
//#define VIEW_ANGLE 43.5  //Axis M1013 camera
#define PI 3.141592653

//Score limits used for target identification
#define RECTANGULARITY_LIMIT 40
#define ASPECT_RATIO_LIMIT 55

//Score limits used for hot target determination
#define TAPE_WIDTH_LIMIT 50
#define VERTICAL_SCORE_LIMIT 50
#define LR_SCORE_LIMIT 50

//Minimum area of particles to be considered
#define AREA_MINIMUM 150

//Maximum number of particles to process
#define MAX_PARTICLES 8

//Structure to represent the scores for the various tests used for target identification
struct Scores {
	double rectangularity;
	double aspectRatioVertical;
	double aspectRatioHorizontal;
};

struct TargetReport {
	int verticalIndex;
	int horizontalIndex;
	bool Hot;
	double totalScore;
	double leftScore;
	double rightScore;
	double tapeWidthScore;
	double verticalScore;
};



Threshold threshold(60, 100, 90, 255, 20, 255); //HSV threshold criteria, ranges are in that order ie. Hue is 60-100
ParticleFilterCriteria2 criteria[] = {
	{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}
						//Particle filter criteria, used to filter out small particles
};

ColorImage *image;
image = new RGBImage("/testImage.jpg");   //get the sample image from the cRio flash
//camera.GetIMage(image);         //To get the images from the camera comment the line above and uncomment this one
BinaryImage *thresholdImage = image->ThresholdHSV(threshold);   // get just the green target pixels
//thresholdImage->Write("/threshold.bmp");
BinaryImage *convexHUllImage = thresholdImage->ConvexHull(false);  //fill in partial and full rectangles
//convexHullImage->Write("/ConvexHull.bmp");
BinaryImage *filteredImage = convexHullImage->ParticleFilter(criteria, 1);  //Remove small particles
//filteredImage->Write("Filtered.bmp");
vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderParticleAnalysisReports();
scores = new Scores[reports->size()];
for (unsigned i = 0; i < reports->size(); i++} {
	ParticleAnalysisReport *report = &(reports->at(i));

	scores[i].rectangularity = scoreRectangularity(report);
	scores[i].aspectRatioOuter = scoreAspectRatio(filteredImage, report, true);
	scores[i].aspectRatioInner = scoreAspectRatio(filteredImage, report, false);
	scores[i].xEdge = scoreXEdge(thresholdImage, report);
	scores[i].yEdge = scoreYEdge(thresholdImage, report);

	if(scoreCompare(scores[i], false))
	{
		printf("particle: %d is a High Goal centerX: %f centerY: %f \n", i, report->center_mass_x_normailized, report->center_mass_y_normailized);
		printf("Distance: %f\n", computeDistance(thresholdImage, report, false));
	}else if (scoreCompare(scores[i], true)}  {
		printf("particle: %d is a Middle Goal centerX: %f centerY: %f \n", i, report->center_mass_x_normailized, report->center_mass_y_normailized);
		printf("Distance: %f\n", computeDistance(thresholdImage, report, true));
	}else {
		printf("particle: %d is not a goal centerX: %f centerY: %f \n", i, report->center_mass_x_normailized, report->center_mass_y_normailized);
	}
	printf("rect: %f ARinner: %f \n", scores[i].rectangularity, scores[i].aspectRatioInner};
	printf("ARouter: %f  xEdge: %f  yEdge: %f \n", scores[i].aspectRatioOUter, scores[i].xEdge, scores[i].yEdge);
}
 //Score Aspect Ratio
double scoreAspectRatio(BinaryImage*image, ParticleAnalysisReport * report, bool vertical){
	double rectLong, rectShort, idealAspectRatio, aspectRatio; 
	idealApsectRatio = vertical ? (4.0/32) : (23.5/4) ; 
	imaqMeasureParticle(image -> GetImaqImage(), report -> particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong); 
	imaqMeasureParticle(image -> GetImaqImage(), report -> particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort); 
	if(report -> boundingRect.width > report -> boundingRect.height){
		aspectRatio = ratioToScore ((( rectLong/ rectShort) / idealAspectRatio)); 
	} else {
		aspectRatio = ratioToScore(((rectShort/rectLong)/idealAspectRatio)); 
	} 
	return aspectRatio; 
} 
double scoreRectangularity(ParticleAnalysisReport *report) {
	if(report->boundingRect.width*report->boundingRect.height !=0) {
		return 100*report->particleArea/ (report->boundingRect.width*report->boundingRect.height);
	} else {
		return 0;
	}
}
double ratioToScore(double ratio)
{
	return (max(0, min(100*(1-fabs(1-ratio)), 100)));
}
bool scoreCompare(Scores scores, bool vertical) {
	bool isTarget = true;

	isTarge &= scores.aspectRatioVertical > RECTANGULARITY_LIMIT;
	if(vertical} {
		isTarget &= scores.aspectRatioVertical > ASPECT_RATIO_LIMIT;
	} else {
		isTarget &= scores.aspectRatioHorizontal > ASPECT_RATIO_LIMIT;
	}
	
	return isTarget;
}
//Zero out scores and set verticalIndex to first target in case there no horizontal targets
target.totalscore = target.leftscore = target.rightscore = target.tapeWidthScore = target.verticalScore = 0;
target.verticalIndex = verticalTargets[0];
for (int i = 0; i < verticalTargetCount; i++)
{
	ParticleAnalysisReport *verticalReport = &(reports->at(verticalTargets[i]});
	for (int j = 0; j < horizontalTargetCount; j++)
	{
		ParticleAnalysisReport *horizontalReport = &(reports->at(horizontalTargets[j]));
		double horizWidth, horizHeight, vertWidth, leftScore, rightScore, tapeWidthScore, verticalScore, total;

		//Measure equivalent rectangle sides for use in score calculation
		imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &horizWidth);
		imaqMeasureParticle(filteredImage->GetImaqImage(), verticalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &vertWidth);
		imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &horizWidth);
	
		//Determine if the horizontal target is in the expected location to the left of the vertical target
		leftScore = ratioToScore(1.2*(verticalReport->boundingRect.left - horizontalReport->center_mass_x)/horizWidth);
		//Determine if the horizontal target is in the expected location to the right of the vertical target
		rightScore = ratioToScore(1.2*(horizontalReport->center_mass_x - verticalReport->boundingRect.left - verticalReport->boundingRect.width)/horizWidth);
		//Determine if the width of the tape on the two targets appears to be the same
		tapeWidthScore = ratioToScore(vertWidth/horizHeight);
		//Determine if the vertical location of the horizontal target appears to be correct
		verticalScore = ratioToScore(1-(verticalReport->boundingRect.top - horizontalReport->center_mass_y)/(4*horizHeight));
		total = leftScore > rightScore ? leftScore:rightScore;
		total += tapewidthScore + verticalScore;

		//If the target is the best detected so far store the information about it
		if(total > target.totalScore)
		{
			target.horizontalIndex = horizontalTargets[j];
			target.verticalIndex = verticalTargets[i];
			target.totalScore = total;
			target.leftScore = leftScore;
			target.rightScore = rightScore;
			target.tapeWidthScore = tapeWidthScore;
			target.verticalScore = verticalScore;
		}
}
//Determine if the best target is a Hot Target
target.Hot = hotOrNot(target);
bool hotOrNot(TargetReport target)
{
	bool isHot = true;
	
	isHot &= target.tapeWidthScore >= TAPE_WIDTH_LIMIT;
	isHot &= target.verticalScore >= VERTICAL_SCORE_LIMIT;
	isHot &= (target.leftScore > LR_SCORE_LIMIT) | (target.rightScore > LR_SCORE_LIMIT);

	return isHot;
}
if(verticalTargetCount > 0)
{
	//Information about the target is contained in the "target" structure
	//To get measurement information such as sizes or location use the
	//horizontal or vertical index to get the particle report as shown below
	ParticleAnalysisReport *distanceReport = &(reports->at(target.verticalIndex));
	double distance = computeDistance(filteredImage, distanceReport);
	if(target.Hot)
	{
		printf("Hot target located \n");
		printf("Distance: %f \n", distance);
	} else {
		printf("No hot target present \n");
		printf("Distance: %f \n", distance);
	}
}
double computeDistance (BinaryImage *image, ParticleAnalysisReport *report) {
	double rectLong, height;
	int targetHeight;
	
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	//using the smaller of the estimated rectangle long side and the bounding rectangle height results in better performance
	//on skewed rectangles
	height = min(report->boundingRect.height, rectLong);
	targetHeight = 32;

	return Y_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(VIEW_ANGLE*PI/ (180*2)));
}

//be sure to delete images after using them
delete filteredImage;
delete thresholdImage;
delet image;

//deleted allocated reports and Scores objects also
delete scores;
delete reports;
	

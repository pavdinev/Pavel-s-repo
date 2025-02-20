import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import numpy as np
import os
from pathlib import Path

for image_name in os. listdir('.'):
  if image_name.endswith(".jpg"):
    img=mpimg.imread(image_name)
    histogram, bin_edges = np.histogram(img, bins=256, range=(0, 255))
    curr_fig=plt.figure()
    plt.xlim([0.0, 255.0])  # <- named arguments do not work here
    plt.ylim([0.0, max(histogram)])
    plt.tick_params(axis='both',left=False, top=False, right=False, bottom=False, labelleft=False, labeltop=False, labelright=False, labelbottom=True)  
    plt.plot(bin_edges[0:-1], histogram,'k')  # <- or here
    plt.fill_between(bin_edges[0:-1], histogram,color = 'k')
    path_to_image=os.getcwd()
    split_image_name=os.path.splitext(image_name)
    suffix='png'
    full_path=os.path.join(path_to_image, split_image_name[0] + "." + suffix)
    curr_fig.savefig(full_path)
    plt.close(curr_fig)
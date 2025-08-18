import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import roc_curve, auc

# Step 1: Generate a synthetic binary classification dataset
X, y = make_classification(n_samples=100000, n_features=10, n_classes=2, random_state=42)

# Step 2: Split the dataset into a training set and a testing set
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# Step 3: Train a classifier (Logistic Regression in this case)
classifier = LogisticRegression()
classifier.fit(X_train, y_train)

# Step 4: Predict probabilities for the test set
y_probs = classifier.predict_proba(X_test)[:, 1]

# Step 5: Compute the ROC curve
fpr, tpr, thresholds = roc_curve(y_test, y_probs)

# Step 6: Compute the AUC (Area Under the Curve)
roc_auc = auc(fpr, tpr)

# Step 7: Plot the ROC curve
plt.figure()
plt.plot(fpr, tpr, color='tab:blue', lw=2, label=f'ROC curve (area = {roc_auc:.2f})')
plt.plot([0, 1], [0, 1], color='gray', lw=2, linestyle='--')  # Diagonal line (random classifier)
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.0])
plt.gca().set_aspect('equal', adjustable='box')

plt.annotate('Ideal TPR & FPR', xy=(0, 1), xytext=(0.3, 0.7),
             arrowprops=dict(color='darkorange', arrowstyle='fancy'),
             fontsize=12, color='darkorange', ha='center')

plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('Receiver Operating Characteristic')
plt.legend(loc="lower right")
plt.savefig('./roc_curve.png', dpi=300, bbox_inches='tight')
plt.show()
